/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/17 23:09:20 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_END,
	TOK_ERROR
}   t_token_type;

/* segment types for tokens: keep quoted/unquoted parts separate */
typedef enum e_seg_type
{
	SEG_UNQUOTED,
	SEG_SINGLE_QUOTED,
	SEG_DOUBLE_QUOTED
} t_seg_type;

typedef struct s_seg
{
	t_seg_type type;
	char *str;
	struct s_seg *next;
} t_seg;

typedef struct s_token
{
    t_token_type    type;
    char            *raw;
	int             no_expand;
	int				in_double;
	/* segments list (created by lexer) */
	t_seg *segs;
	struct s_token  *next;
}   t_token;

t_token *lexer_tokenize(const char *line);
void    token_free_all(t_token *tok);

/* helpers provided by token_utils.c */
t_token *token_new(t_token_type type, const char *raw);
void    token_append(t_token **head, t_token *node);

/* helpers split into helpers file */
int append_word_token(const char *line, size_t start, size_t end,
                        t_token **head);
int     collect_word(const char *line, size_t *i, size_t len, t_token **head);
int     handle_redir(const char *line, size_t *i, size_t len, t_token **head);

/* expansion (expander) */
void    expand_tokens(t_token *head, char **envp, int last_status);

#endif
