/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:53 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/18 19:16:25 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parse_tokens(t_token *tokens);
void	free_commands(t_cmd *cmds);

t_cmd	*cmd_new(void);
int		add_arg(t_cmd *cmd, const char *arg);
int		add_redir(t_cmd *cmd, t_redir_type type, const char *target);
t_cmd	*ensure_cmd(t_cmd **head, t_cmd **cur);
t_token	*parse_word_token(t_token *tk, t_cmd **head, t_cmd **cur);
t_token	*parse_redir_token(t_token *tk, t_cmd **head, t_cmd **cur);
t_token	*parse_pipe_token(t_token *tk, t_cmd **head, t_cmd **cur);
t_token	*parse_error_token(t_token *tk, t_cmd **head);
char	*create_heredoc(t_token *delim_token);

#endif
