/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:10:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/18 19:27:16 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>

static int	should_expand(t_token *delim_token)
{
	t_seg	*s;

	if (!delim_token->segs)
		return (1);
	s = delim_token->segs;
	while (s)
	{
		if (s->type == SEG_SINGLE_QUOTED || s->type == SEG_DOUBLE_QUOTED)
			return (0);
		s = s->next;
	}
	return (1);
}

static char	*read_heredoc_lines(const char *delimiter, int expand)
{
	char	*line;
	char	template[32];
	int		fd;

	(void)expand;
	strcpy(template, "/tmp/minishell_heredoc_XXXXXX");
	fd = mkstemp(template);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (strdup(template));
}

char	*create_heredoc(t_token *delim_token)
{
	int		expand;
	char	*tmpfile;

	expand = should_expand(delim_token);
	tmpfile = read_heredoc_lines(delim_token->raw, expand);
	return (tmpfile);
}
