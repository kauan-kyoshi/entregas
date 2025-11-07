/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:01 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc < 2)
		return (0);
	stack = init_stack();
	if (!stack)
		return (write(2, "Error\n", 6), 1);
	if (!parse_arguments(argc, argv, stack))
	{
		write(2, "Error\n", 6);
		free_stack(stack);
		return (1);
	}
	sort_stack(stack);
	free_stack(stack);
	return (0);
}
