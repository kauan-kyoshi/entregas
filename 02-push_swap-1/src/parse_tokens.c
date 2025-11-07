/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:33 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:34 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ps_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

int	ps_process_single_arg(char *arg, t_stack *stack)
{
	char	**split;
	int		i;
	long	num;
	int		*value;

	split = ft_split(arg, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		if (!is_valid_number(split[i]))
			return (free_split(split), 0);
		num = ft_atol(split[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (free_split(split), 0);
		value = malloc(sizeof(int));
		if (!value)
			return (free_split(split), 0);
		*value = (int)num;
		ft_push_lst_dlist(stack->a, value);
		i++;
	}
	free_split(split);
	return (1);
}
