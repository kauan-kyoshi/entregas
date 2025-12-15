/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+ +#+           */
/*   Created: 2025/11/26 18:40:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/26 18:40:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int	append_word_token(const char *line, size_t start,
					size_t end, t_token **head)
{
	char	*raw;
	t_token	*t;

	raw = malloc(end - start + 1);
	if (!raw)
		return (-1);
	memcpy(raw, line + start, end - start);
	raw[end - start] = '\0';
	t = token_new(TOK_WORD, raw);
	free(raw);
	if (!t)
		return (-1);
	token_append(head, t);
	return (0);
}

static int	make_and_append(t_token **head, t_token_type type,
const char *s, size_t *i)
{
	t_token	*t;

	t = token_new(type, s);
	if (!t)
		return (0);
	token_append(head, t);
	*i += strlen(s);
	return (1);
}

int	handle_redir(const char *line, size_t *i, size_t len, t_token **head)
{
	if (*i >= len)
		return (0);
	if (line[*i] == '>')
	{
		if (*i + 1 < len && line[*i + 1] == '>')
			return (make_and_append(head, TOK_REDIR_APPEND, ">>", i));
		return (make_and_append(head, TOK_REDIR_OUT, ">", i));
	}
	if (line[*i] == '<')
	{
		if (*i + 1 < len && line[*i + 1] == '<')
			return (make_and_append(head, TOK_HEREDOC, "<<", i));
		return (make_and_append(head, TOK_REDIR_IN, "<", i));
	}
	return (0);
}

/* helper to detect word-breaking characters */
int	collect_word(const char *line, size_t *i, size_t len, t_token **head)
{
	size_t  buf_cap;
	size_t  buf_len;
	char    *buf;
	int     seen_single;
	int     seen_other;

	buf_cap = 64;
	buf_len = 0;
	seen_single = 0;
	seen_other = 0;
	buf = malloc(buf_cap);
	if (!buf)
		return (-1);
	while (*i < len)
	{
		if (line[*i] == '\'')
		{
			/* single quotes: copy literally until closing quote */
			(*i)++;
			seen_single = 1;
			while (*i < len && line[*i] != '\'')
			{
				if (buf_len + 1 >= buf_cap)
				{
					buf_cap *= 2;
					buf = realloc(buf, buf_cap);
					if (!buf)
						return (-1);
				}
				buf[buf_len++] = line[*i];
				(*i)++;
			}
			if (*i >= len)
			{
				free(buf);
				token_free_all(*head);
				*head = token_new(TOK_ERROR, "unterminated_quote");
				return (-2);
			}
			(*i)++;
			continue ;
		}
		if (line[*i] == '"')
		{
			/* double quotes: copy content (expansion handled later) */
			(*i)++;
			seen_other = 1;
			while (*i < len && line[*i] != '"')
			{
				if (buf_len + 1 >= buf_cap)
				{
					buf_cap *= 2;
					buf = realloc(buf, buf_cap);
					if (!buf)
						return (-1);
				}
				buf[buf_len++] = line[*i];
				(*i)++;
			}
			if (*i >= len)
			{
				free(buf);
				token_free_all(*head);
				*head = token_new(TOK_ERROR, "unterminated_quote");
				return (-2);
			}
			(*i)++;
			continue ;
		}
		if (isspace((unsigned char)line[*i]) || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
			break;
		if (buf_len + 1 >= buf_cap)
		{
			buf_cap *= 2;
			buf = realloc(buf, buf_cap);
			if (!buf)
				return (-1);
		}
		buf[buf_len++] = line[*i];
		(*i)++;
	}
	buf[buf_len] = '\0';
	{
		t_token *t;

		t = token_new(TOK_WORD, buf);
		free(buf);
		if (!t)
			return (-1);
		/* if token was built only from single-quoted parts, disable expansion */
		if (seen_single && !seen_other)
			t->no_expand = 1;
		token_append(head, t);
	}
	return (0);
}

/* create_and_append removed: token creation happens in lexer.c to satisfy
   Norminette function/count limits. */
