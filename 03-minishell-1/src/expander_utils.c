/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
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

int	expand_buf(t_exp *ctx, const char *str)
{
	size_t	need;

	need = ctx->out_len + strlen(str) + 1;
	if (need > ctx->cap)
	{
		ctx->cap = need * 2;
		ctx->out = realloc(ctx->out, ctx->cap);
		if (!ctx->out)
			return (0);
	}
	strcpy(ctx->out + ctx->out_len, str);
	ctx->out_len += strlen(str);
	return (1);
}

int	expand_char(t_exp *ctx)
{
	if (ctx->out_len + 2 > ctx->cap)
	{
		ctx->cap = (ctx->out_len + 2) * 2;
		ctx->out = realloc(ctx->out, ctx->cap);
		if (!ctx->out)
			return (0);
	}
	return (1);
}

void	rebuild_raw(t_token *tk)
{
	size_t	total;
	t_seg	*it;

	total = 0;
	it = tk->segs;
	while (it)
	{
		total += strlen(it->str);
		it = it->next;
	}
	free(tk->raw);
	tk->raw = malloc(total + 1);
	if (!tk->raw)
		return ;
	tk->raw[0] = '\0';
	it = tk->segs;
	while (it)
	{
		strcat(tk->raw, it->str);
		it = it->next;
	}
}
