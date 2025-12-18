/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:28:56 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/18 12:46:17 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdio.h>

static const char *redir_type_name(t_redir_type t)
{
    if (t == REDIR_IN) return "REDIR_IN";
    if (t == REDIR_OUT) return "REDIR_OUT";
    if (t == HEREDOC) return "HEREDOC";
    if (t == APPEND) return "APPEND";
    return "UNKNOWN";
}

void exec_cmd(t_cmd *cmd)
{
    int idx = 0;
    t_cmd *c = cmd;

    while (c)
    {
        printf("Command %d:\n", idx);
        if (c->args)
        {
            size_t i = 0;
            while (c->args[i])
            {
                printf("  argv[%zu] = %s\n", i, c->args[i]);
                i++;
            }
        }
        else
        {
            printf("  (no argv)\n");
        }

        t_redir *r = c->redirs;
        while (r)
        {
            printf("  redir type=%s target=%s\n", redir_type_name(r->type), r->file ? r->file : "(null)");
            r = r->next;
        }

        c = c->next;
        idx++;
    }
}