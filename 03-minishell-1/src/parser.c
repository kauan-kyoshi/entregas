/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:47 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/17 23:11:50 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <readline/readline.h>
#include <ctype.h>

static t_cmd *cmd_new(void)
{
    t_cmd *c;

    c = malloc(sizeof(t_cmd));
    if (!c)
        return (NULL);
    c->args = NULL;
    c->redirs = NULL;
    c->next = NULL;
    return (c);
}

static int add_arg(t_cmd *cmd, const char *arg)
{
    size_t  cnt;
    char    **newargv;

    if (!cmd)
        return (-1);
    cnt = 0;
    if (cmd->args)
    {
        while (cmd->args[cnt])
            cnt++;
    }
    newargv = malloc(sizeof(char *) * (cnt + 2));
    if (!newargv)
        return (-1);
    if (cmd->args)
    {
        for (size_t i = 0; i < cnt; i++)
            newargv[i] = cmd->args[i];
        free(cmd->args);
    }
    newargv[cnt] = strdup(arg);
    newargv[cnt + 1] = NULL;
    cmd->args = newargv;
    return (0);
}

static int add_redir(t_cmd *cmd, t_redir_type type, const char *target)
{
    t_redir *r;

    if (!cmd || !target)
        return (-1);
    r = malloc(sizeof(t_redir));
    if (!r)
        return (-1);
    r->type = type;
    r->file = strdup(target);
    r->next = cmd->redirs;
    cmd->redirs = r;
    return (0);
}

static void free_redirs(t_redir *r)
{
    t_redir *tmp;

    while (r)
    {
        tmp = r->next;
        if (r->file)
            free(r->file);
        free(r);
        r = tmp;
    }
}

void free_commands(t_cmd *cmds)
{
    t_cmd *c;
    t_cmd *tmp;
    size_t i;

    c = cmds;
    while (c)
    {
        tmp = c->next;
        if (c->args)
        {
            for (i = 0; c->args[i]; i++)
                free(c->args[i]);
            free(c->args);
        }
        free_redirs(c->redirs);
        free(c);
        c = tmp;
    }
}

/* debug printing removed */

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *head = NULL;
    t_cmd *cur = NULL;
    t_token *tk = tokens;

    while (tk)
    {
        if (tk->type == TOK_WORD)
        {
            if (!cur)
            {
                cur = cmd_new();
                if (!cur)
                    return (NULL);
                if (!head)
                    head = cur;
            }
            if (add_arg(cur, tk->raw) == -1)
            {
                free_commands(head);
                return (NULL);
            }
        }
        else if (tk->type == TOK_REDIR_IN || tk->type == TOK_REDIR_OUT || tk->type == TOK_REDIR_APPEND || tk->type == TOK_HEREDOC)
        {
            t_redir_type rt;
            t_token *next;

            if (tk->type == TOK_REDIR_IN)
                rt = REDIR_IN;
            else if (tk->type == TOK_REDIR_OUT)
                rt = REDIR_OUT;
            else if (tk->type == TOK_REDIR_APPEND)
                rt = APPEND;
            else
                rt = HEREDOC;
            next = tk->next;
            if (!next || next->type != TOK_WORD)
            {
                fprintf(stderr, "parse error: redirection without target\n");
                free_commands(head);
                return (NULL);
            }
            if (!cur)
            {
                cur = cmd_new();
                if (!cur)
                    return (NULL);
                if (!head)
                    head = cur;
            }
            if (rt == HEREDOC)
            {
                /* handle heredoc: read lines until delimiter (next->raw)
                   If the delimiter token was quoted, do not expand heredoc content. */
                int expand = 1;
                if (next->segs)
                {
                    for (t_seg *s = next->segs; s; s = s->next)
                    {
                        if (s->type == SEG_SINGLE_QUOTED || s->type == SEG_DOUBLE_QUOTED)
                        {
                            expand = 0;
                            break;
                        }
                    }
                }
                /* create tmpfile and write heredoc content */
                char template[] = "/tmp/minishell_heredoc_XXXXXX";
                int fd = mkstemp(template);
                if (fd == -1)
                {
                    perror("mkstemp");
                    free_commands(head);
                    return (NULL);
                }
                while (1)
                {
                    char *line = readline("heredoc> ");
                    if (!line)
                    {
                        /* EOF (Ctrl-D) */
                        break;
                    }
                    if (strcmp(line, next->raw) == 0)
                    {
                        free(line);
                        break;
                    }
                    char *out_line = NULL;
                    if (expand)
                    {
                        /* expand $VAR and $? in the line - simple expansion */
                        size_t cap = strlen(line) + 1;
                        out_line = malloc(cap);
                        if (!out_line)
                        {
                            free(line);
                            close(fd);
                            free_commands(head);
                            return (NULL);
                        }
                        size_t out_len = 0;
                        for (size_t i = 0; line[i]; )
                        {
                            if (line[i] == '$')
                            {
                                if (line[i+1] == '?')
                                {
                                    char numbuf[32];
                                    int l = snprintf(numbuf, sizeof(numbuf), "%d", 0);
                                    size_t need = out_len + (size_t)l + 1;
                                    if (need > cap)
                                    {
                                        cap = need * 2;
                                        out_line = realloc(out_line, cap);
                                        if (!out_line) { free(line); close(fd); free_commands(head); return (NULL); }
                                    }
                                    memcpy(out_line + out_len, numbuf, l);
                                    out_len += l;
                                    i += 2;
                                    continue;
                                }
                                if (isalpha((unsigned char)line[i+1]) || line[i+1] == '_')
                                {
                                    size_t j = i+1;
                                    while (line[j] && (isalnum((unsigned char)line[j]) || line[j] == '_')) j++;
                                    size_t namelen = j - (i+1);
                                    char *name = malloc(namelen + 1);
                                    if (!name) { free(line); close(fd); free_commands(head); return (NULL); }
                                    memcpy(name, line + i + 1, namelen);
                                    name[namelen] = '\0';
                                    extern char **environ;
                                    char *val = NULL;
                                    for (size_t e = 0; environ && environ[e]; e++)
                                    {
                                        if (strncmp(environ[e], name, namelen) == 0 && environ[e][namelen] == '=')
                                        {
                                            val = environ[e] + namelen + 1;
                                            break;
                                        }
                                    }
                                    if (!val) val = "";
                                    size_t need = out_len + strlen(val) + 1;
                                    if (need > cap)
                                    {
                                        cap = need * 2;
                                        out_line = realloc(out_line, cap);
                                        if (!out_line) { free(name); free(line); close(fd); free_commands(head); return (NULL); }
                                    }
                                    strcpy(out_line + out_len, val);
                                    out_len += strlen(val);
                                    free(name);
                                    i = j;
                                    continue;
                                }
                                if (out_len + 2 > cap) { cap = (out_len + 2) * 2; out_line = realloc(out_line, cap); if (!out_line) { free(line); close(fd); free_commands(head); return (NULL); } }
                                out_line[out_len++] = '$';
                                i++;
                                continue;
                            }
                            if (out_len + 2 > cap) { cap = (out_len + 2) * 2; out_line = realloc(out_line, cap); if (!out_line) { free(line); close(fd); free_commands(head); return (NULL); } }
                            out_line[out_len++] = line[i++];
                        }
                        out_line[out_len] = '\0';
                    }
                    else
                    {
                        out_line = strdup(line);
                    }
                    if (out_line)
                    {
                        write(fd, out_line, strlen(out_line));
                        write(fd, "\n", 1);
                        free(out_line);
                    }
                    free(line);
                }
                close(fd);
                if (add_redir(cur, rt, template) == -1)
                {
                    free_commands(head);
                    return (NULL);
                }
                tk = next; /* consume target */
            }
            else
            {
                if (add_redir(cur, rt, next->raw) == -1)
                {
                    free_commands(head);
                    return (NULL);
                }
                tk = next; /* consume target */
            }
        }
        else if (tk->type == TOK_PIPE)
        {
            if (!cur)
            {
                fprintf(stderr, "parse error: pipe with no command before\n");
                free_commands(head);
                return (NULL);
            }
            /* start a new command */
            cur->next = cmd_new();
            if (!cur->next)
            {
                free_commands(head);
                return (NULL);
            }
            cur = cur->next;
        }
        else if (tk->type == TOK_ERROR)
        {
            fprintf(stderr, "lexer error token: %s\n", tk->raw ? tk->raw : "(null)");
            free_commands(head);
            return (NULL);
        }
        tk = tk->next;
    }
    return (head);
}


/* parser() wrapper removed; use parse_tokens(tokens) directly */