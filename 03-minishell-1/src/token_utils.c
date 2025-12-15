/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:04:12 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/27 16:16:08 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_token	*token_new(t_token_type type, const char *str)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->raw = NULL;
	t->no_expand = 0;
	if (str)
	{
		t->raw = malloc(strlen(str) + 1);
		if (!t->raw)
		{
			free(t);
			return (NULL);
		}
		strcpy(t->raw, str);
	}
	t->next = NULL;
	return (t);
}

void	token_append(t_token **head, t_token *node)
{
	t_token	*it;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	it = *head;
	while (it->next)
		it = it->next;
	it->next = node;
}

void	token_free_all(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->raw)
			free(head->raw);
		free(head);
		head = tmp;
	}
}

void	token_debug_print(const t_token *head)
{
	const char	*val;

	while (head)
	{
		if (head->raw)
			val = head->raw;
		else
			val = "(null)";
		printf("type=%d raw=%s\n", head->type, val);
		head = head->next;
	}
}
