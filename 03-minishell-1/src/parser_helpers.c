/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
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

t_token	*parse_word_token(t_token *tk, t_cmd **head, t_cmd **cur)
{
	if (!ensure_cmd(head, cur))
		return (NULL);
	if (add_arg(*cur, tk->raw) == -1)
	{
		free_commands(*head);
		return (NULL);
	}
	return (tk->next);
}

t_token	*parse_pipe_token(t_token *tk, t_cmd **head, t_cmd **cur)
{
	if (!*cur)
	{
		fprintf(stderr, "parse error: pipe with no command before\n");
		free_commands(*head);
		return (NULL);
	}
	(*cur)->next = cmd_new();
	if (!(*cur)->next)
	{
		free_commands(*head);
		return (NULL);
	}
	*cur = (*cur)->next;
	return (tk->next);
}

t_token	*parse_error_token(t_token *tk, t_cmd **head)
{
	const char	*msg;

	if (tk->raw)
		msg = tk->raw;
	else
		msg = "(null)";
	fprintf(stderr, "lexer error token: %s\n", msg);
	free_commands(*head);
	return (NULL);
}
