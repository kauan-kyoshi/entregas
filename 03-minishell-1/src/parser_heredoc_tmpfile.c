/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_tmpfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/22 17:23:18 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

static int	init_tmpdir(void)
{
	if (mkdir("tmp", S_IRWXU) == -1)
	{
		if (errno != EEXIST)
			return (-1);
	}
	return (0);
}

static int	try_tmpfile_loop(char *out, size_t out_sz, pid_t pid, int *seq)
{
	char	name[128];
	int		fd;

	while (*seq < 100000)
	{
		if (build_tmp_name(name, pid, *seq) == -1)
			return (-1);
		fd = try_create_tmp(name, out, out_sz);
		if (fd != -1)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		(*seq)++;
	}
	return (-1);
}

int	open_unique_tmpfile(char *out, size_t out_sz)
{
	pid_t		pid;
	static int	seq;

	if (init_tmpdir() == -1)
		return (-1);
	pid = getpid();
	seq++;
	if (seq <= 0)
		seq = 1;
	return (try_tmpfile_loop(out, out_sz, pid, &seq));
}
