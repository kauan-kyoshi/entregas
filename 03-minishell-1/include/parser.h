/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:26:53 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/28 14:35:28 by kakubo-l         ###   ########.fr       */
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
void    print_commands(t_cmd *cmds);
void    free_commands(t_cmd *cmds);
t_redir *new_redir(t_redir_type type, char *filename);
t_cmd *new_cmd(char **args);
t_cmd *populate_struct_manual(void);
void print_pipeline_structure(t_cmd *cmd_list);
t_cmd *pupulate_struct(void);
t_cmd *parser(void);

#endif
