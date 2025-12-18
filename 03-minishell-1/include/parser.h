/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:53 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/17 23:09:02 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
typedef enum e_redir_type
{
	REDIR_IN,    // <
	REDIR_OUT,   // >
	HEREDOC,     // <<
	APPEND       // >>
} t_redir_type;

/* Estrutura Auxiliar: Guarda UM redirecionamento */
typedef struct s_redir
{
	t_redir_type    type;      // Qual o símbolo? (<, >, <<, >>)
	char            *file;     // Qual o arquivo ou delimitador? ("log.txt")
	struct s_redir  *next;     // Próximo redirecionamento do MESMO comando
} t_redir;

/* ESTRUTURA PRINCIPAL: O Comando (Vagão) */
typedef struct s_cmd
{
	char            **args;    // O comando e flags para o execve (ex: {"grep", "erro", NULL})
	t_redir         *redirs;   // Lista de entradas/saídas deste comando específico
	struct s_cmd    *next;     // Próximo comando APÓS o pipe (|)
} t_cmd;

t_cmd   *parse_tokens(t_token *tokens);
void    free_commands(t_cmd *cmds);
/* parser() wrapper removed; use parse_tokens() directly */

#endif
