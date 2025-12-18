/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/18 18:05:56 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*get_env_value(char **envp, const char *name)
{
	size_t	len;
	size_t	i;

	len = strlen(name);
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*int_to_str(int n)
{
	char	buf[32];
	int		len;

	len = snprintf(buf, sizeof(buf), "%d", n);
	if (len < 0)
		return (NULL);
	return (strdup(buf));
}

int	expand_status(t_exp *ctx, size_t *i)
{
	char	*code;

	code = int_to_str(ctx->last_status);
	if (!code)
		return (0);
	if (!expand_buf(ctx, code))
	{
		free(code);
		return (0);
	}
	free(code);
	*i += 2;
	return (1);
}
