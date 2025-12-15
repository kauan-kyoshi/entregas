/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/27 16:16:08 by kakubo-l         ###   ########.fr       */
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

typedef struct s_token
{
    t_token_type    type;
    char            *raw;
	int             no_expand;
    struct s_token  *next;
}   t_token;

t_token *lexer_tokenize(const char *line);
void    token_free_all(t_token *tok);
void    token_debug_print(const t_token *tok);

/* helpers provided by token_utils.c */
t_token *token_new(t_token_type type, const char *raw);
void    token_append(t_token **head, t_token *node);

/* helpers split into helpers file */
int append_word_token(const char *line, size_t start, size_t end,
                        t_token **head);
int     collect_word(const char *line, size_t *i, size_t len, t_token **head);
int     handle_redir(const char *line, size_t *i, size_t len, t_token **head);

#endif
