/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:03:51 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 17:03:52 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	move_to_top_b(t_stack *stack, int position)
{
	int		dist_top;
	int		size;

	size = (int)stack->b->size;
	if (position <= size / 2)
	{
		dist_top = position;
		while (dist_top > 0)
		{
			rb(stack, 1);
			dist_top--;
		}
	}
	else
	{
		dist_top = size - position;
		while (dist_top > 0)
		{
			rrb(stack, 1);
			dist_top--;
		}
	}
}

void	phase_pull_b_to_a(t_stack *stack, int size)
{
	while (size > 0)
	{
		move_to_top_b(stack, find_position(stack->b, size - 1));
		pa(stack, 1);
		size--;
	}
}
