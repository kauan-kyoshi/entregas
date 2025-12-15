/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:47 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/28 14:46:33 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

void print_commands(t_cmd *cmds)
{
    int idx = 0;
    t_cmd *c = cmds;

    while (c)
    {
        printf("Command %d:\n", idx);
        if (c->args)
        {
            for (size_t i = 0; c->args[i]; i++)
                printf("  argv[%zu] = %s\n", i, c->args[i]);
        }
        else
            printf("  (no argv)\n");
        if (c->redirs)
        {
            t_redir *r = c->redirs;
            while (r)
            {
                printf("  redir type=%d target=%s\n", r->type, r->file);
                r = r->next;
            }
        }
        c = c->next;
        idx++;
    }
}
/*
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
                return (NULL);
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
            if (add_redir(cur, rt, next->raw) == -1)
            {
                free_commands(head);
                return (NULL);
            }
            tk = next; /* consume target 
        }
        else if (tk->type == TOK_PIPE)
        {
            if (!cur)
            {
                fprintf(stderr, "parse error: pipe with no command before\n");
                free_commands(head);
                return (NULL);
            }
            /* start a new command
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
*/


t_cmd *parser(void)
{
    return pupulate_struct();
}