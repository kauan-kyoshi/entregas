/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/18 19:19:34 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static t_redir_type	get_redir_type(t_token_type type)
{
	t_redir_type	rt;

	if (type == TOK_REDIR_IN)
		rt = REDIR_IN;
	else if (type == TOK_REDIR_OUT)
		rt = REDIR_OUT;
	else if (type == TOK_REDIR_APPEND)
		rt = APPEND;
	else
		rt = HEREDOC;
	return (rt);
}

static char	*get_redir_target(t_redir_type rt, t_token *next)
{
	char	*target;

	if (rt == HEREDOC)
		target = create_heredoc(next);
	else
		target = strdup(next->raw);
	return (target);
}

static int	process_redir(t_cmd **cur, t_redir_type rt, char *target)
{
	int	result;

	result = add_redir(*cur, rt, target);
	free(target);
	return (result);
}

t_token	*parse_redir_token(t_token *tk, t_cmd **head, t_cmd **cur)
{
	t_redir_type	rt;
	t_token			*next;
	char			*target;

	rt = get_redir_type(tk->type);
	next = tk->next;
	if (!next || next->type != TOK_WORD)
	{
		fprintf(stderr, "parse error: redirection without target\n");
		free_commands(*head);
		return (NULL);
	}
	if (!ensure_cmd(head, cur))
		return (NULL);
	target = get_redir_target(rt, next);
	if (!target || process_redir(cur, rt, target) == -1)
	{
		free_commands(*head);
		return (NULL);
	}
	return (next->next);
}
