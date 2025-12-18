/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/17 21:54:39 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"
#include "lexer.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
/* lexer/parser inspection removed; restore normal prompt behavior */

volatile sig_atomic_t	g_last_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_last_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction(SIGINT)");
	sa.sa_handler = sigquit_handler;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("sigaction(SIGQUIT)");
}

int	main(void)
{
	char	*line;
    t_cmd   *cmd;
    t_token *tokens;
    extern char **environ;
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			/* tokenize -> expand -> parse -> exec (exec is still a stub) */
			tokens = lexer_tokenize(line);
			if (tokens)
			{
				expand_tokens(tokens, environ, 0);
				cmd = parse_tokens(tokens);
				token_free_all(tokens);
				if (cmd)
				{
					exec_cmd(cmd);
					free_commands(cmd);
				}
			}
		}
		free(line);
	}
	return (0);
}
