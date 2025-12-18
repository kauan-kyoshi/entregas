/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:53:24 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/17 22:17:16 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static char *get_env_value(char **envp, const char *name)
{
    size_t len = strlen(name);
    if (!envp)
        return NULL;
    for (size_t i = 0; envp[i]; i++)
    {
        if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return envp[i] + len + 1;
    }
    return NULL;
}

static char *int_to_str(int n)
{
    char buf[32];
    int len;

    len = snprintf(buf, sizeof(buf), "%d", n);
    if (len < 0)
        return NULL;
    return strdup(buf);
}

void expand_tokens(t_token *head, char **envp, int last_status)
{
    t_token *tk = head;

    while (tk)
    {
        if (tk->type != TOK_WORD)
        {
            tk = tk->next;
            continue;
        }
        if (tk->no_expand)
        {
            tk = tk->next;
            continue;
        }
        /* expand each segment separately (skip single-quoted segments) */
        if (tk->segs)
        {
            for (t_seg *seg = tk->segs; seg; seg = seg->next)
            {
                if (seg->type == SEG_SINGLE_QUOTED)
                    continue;
                const char *s = seg->str ? seg->str : "";
                size_t cap = strlen(s) + 1;
                char *out = malloc(cap);
                if (!out)
                    return;
                size_t out_len = 0;
                for (size_t i = 0; s[i]; )
                {
                    if (s[i] == '$')
                    {
                        if (s[i + 1] == '?')
                        {
                            char *code = int_to_str(last_status);
                            if (code)
                            {
                                size_t need = out_len + strlen(code) + 1;
                                if (need > cap)
                                {
                                    cap = need * 2;
                                    out = realloc(out, cap);
                                    if (!out)
                                    {
                                        free(code);
                                        return;
                                    }
                                }
                                strcpy(out + out_len, code);
                                out_len += strlen(code);
                                free(code);
                            }
                            i += 2;
                            continue;
                        }
                        if (isalpha((unsigned char)s[i + 1]) || s[i + 1] == '_')
                        {
                            size_t j = i + 1;
                            while (s[j] && (isalnum((unsigned char)s[j]) || s[j] == '_'))
                                j++;
                            size_t namelen = j - (i + 1);
                            char *name = malloc(namelen + 1);
                            if (!name)
                            {
                                free(out);
                                return;
                            }
                            memcpy(name, s + i + 1, namelen);
                            name[namelen] = '\0';
                            char *val = get_env_value(envp, name);
                            if (!val)
                                val = "";
                            size_t need = out_len + strlen(val) + 1;
                            if (need > cap)
                            {
                                cap = need * 2;
                                out = realloc(out, cap);
                                if (!out)
                                {
                                    free(name);
                                    return;
                                }
                            }
                            strcpy(out + out_len, val);
                            out_len += strlen(val);
                            free(name);
                            i = j;
                            continue;
                        }
                        if (out_len + 2 > cap)
                        {
                            cap = (out_len + 2) * 2;
                            out = realloc(out, cap);
                            if (!out)
                                return;
                        }
                        out[out_len++] = '$';
                        i++;
                        continue;
                    }
                    if (out_len + 2 > cap)
                    {
                        cap = (out_len + 2) * 2;
                        out = realloc(out, cap);
                        if (!out)
                            return;
                    }
                    out[out_len++] = s[i++];
                }
                out[out_len] = '\0';
                free(seg->str);
                seg->str = strdup(out);
                free(out);
            }
            /* rebuild tk->raw */
            size_t total = 0;
            for (t_seg *it = tk->segs; it; it = it->next) total += strlen(it->str);
            free(tk->raw);
            tk->raw = malloc(total + 1);
            if (!tk->raw)
                return;
            tk->raw[0] = '\0';
            for (t_seg *it = tk->segs; it; it = it->next) strcat(tk->raw, it->str);
        }
        tk = tk->next;
    }
}
