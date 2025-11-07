/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:31 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	push_single_value(char *arg, t_stack *stack)
{
	long	num;
	int		*value;

	if (!is_valid_number(arg))
		return (0);
	num = ft_atol(arg);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	value = malloc(sizeof(int));
	if (!value)
		return (0);
	*value = (int)num;
	ft_push_lst_dlist(stack->a, value);
	return (1);
}

int	parse_arguments(int argc, char **argv, t_stack *stack)
{
	int	i;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (ps_count_words(argv[i], ' ') > 1)
		{
			if (!ps_process_single_arg(argv[i], stack))
				return (0);
		}
		else if (!push_single_value(argv[i], stack))
			return (0);
		i++;
	}
	if (ps_check_duplicates_in_stack(stack->a))
		return (0);
	ps_index_stack(stack);
	return (1);
}
