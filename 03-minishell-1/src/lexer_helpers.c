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

	/* build a list of segments for this word, preserving quoting context */
	 t_seg *segs = NULL;
	 t_seg *last = NULL;
	 int seen_single = 0;
	 int seen_double = 0;

	 while (*i < len)
	 {
		 if (line[*i] == '\'')
		 {
			 /* single-quoted segment */
			 size_t start = ++(*i);
			 while (*i < len && line[*i] != '\'')
				 (*i)++;
			 if (*i >= len)
			 {
				 token_free_all(*head);
				 *head = token_new(TOK_ERROR, "unterminated_quote");
				 return (-2);
			 }
			 size_t slen = *i - start;
			 char *s = malloc(slen + 1);
			 if (!s)
			 {
				 /* cleanup */
				 t_seg *it = segs;
				 while (it) { t_seg *n = it->next; free(it->str); free(it); it = n; }
				 return (-1);
			 }
			 memcpy(s, line + start, slen);
			 s[slen] = '\0';
			 t_seg *node = malloc(sizeof(t_seg));
			 if (!node) { free(s); return (-1); }
			 node->type = SEG_SINGLE_QUOTED;
			 node->str = s;
			 node->next = NULL;
			 if (last) last->next = node; else segs = node;
			 last = node;
			 seen_single = 1;
			 (*i)++; /* skip closing quote */
			 continue;
		 }
		 if (line[*i] == '"')
		 {
			 /* double-quoted segment */
			 size_t start = ++(*i);
			 while (*i < len && line[*i] != '"')
				 (*i)++;
			 if (*i >= len)
			 {
				 token_free_all(*head);
				 *head = token_new(TOK_ERROR, "unterminated_quote");
				 return (-2);
			 }
			 size_t slen = *i - start;
			 char *s = malloc(slen + 1);
			 if (!s) { /* cleanup */ t_seg *it = segs; while (it) { t_seg *n = it->next; free(it->str); free(it); it = n; } return (-1); }
			 memcpy(s, line + start, slen);
			 s[slen] = '\0';
			 t_seg *node = malloc(sizeof(t_seg));
			 if (!node) { free(s); return (-1); }
			 node->type = SEG_DOUBLE_QUOTED;
			 node->str = s;
			 node->next = NULL;
			 if (last) last->next = node; else segs = node;
			 last = node;
			 seen_double = 1;
			 (*i)++; /* skip closing quote */
			 continue;
		 }
		 if (isspace((unsigned char)line[*i]) || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
			 break;
		 /* unquoted segment */
		 size_t start = *i;
		 while (*i < len && !isspace((unsigned char)line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '"' && line[*i] != '\'')
			 (*i)++;
		 size_t slen = *i - start;
		 char *s = malloc(slen + 1);
		 if (!s) { t_seg *it = segs; while (it) { t_seg *n = it->next; free(it->str); free(it); it = n; } return (-1); }
		 memcpy(s, line + start, slen);
		 s[slen] = '\0';
		 t_seg *node = malloc(sizeof(t_seg));
		 if (!node) { free(s); return (-1); }
		 node->type = SEG_UNQUOTED;
		 node->str = s;
		 node->next = NULL;
		 if (last) last->next = node; else segs = node;
		 last = node;
	 }

	 if (!segs)
	 {
		 /* nothing collected */
		 t_token *t = token_new(TOK_WORD, "");
		 if (!t) return (-1);
		 token_append(head, t);
		 return (0);
	 }

	 /* determine flags */
	 int all_single = 1;
	 for (t_seg *it = segs; it; it = it->next)
	 {
		 if (it->type != SEG_SINGLE_QUOTED)
		 {
			 all_single = 0;
			 break;
		 }
	 }

	 /* create token and attach segments */
	 t_token *t = token_new(TOK_WORD, NULL);
	 if (!t)
	 {
		 t_seg *it = segs;
		 while (it) { t_seg *n = it->next; free(it->str); free(it); it = n; }
		 return (-1);
	 }
	 t->segs = segs;
	 t->no_expand = all_single ? 1 : 0;
	 t->in_double = seen_double ? 1 : 0;

	 /* build raw by concatenating segments */
	 size_t total = 0;
	 for (t_seg *it = segs; it; it = it->next) total += strlen(it->str);
	 t->raw = malloc(total + 1);
	 if (!t->raw)
	 {
		 /* cleanup */
		 t_seg *it = segs; while (it) { t_seg *n = it->next; free(it->str); free(it); it = n; }
		 free(t);
		 return (-1);
	 }
	 t->raw[0] = '\0';
	 for (t_seg *it = segs; it; it = it->next) strcat(t->raw, it->str);
	 token_append(head, t);
	 return (0);
}

