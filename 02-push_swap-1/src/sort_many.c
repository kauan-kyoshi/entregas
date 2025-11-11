/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_many.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:36 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:09:34 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	move_to_top_b(t_stack *stack, int position)
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

static void	phase_push_a_to_b(t_stack *stack, int chunk_size)
{
	int	pushed_count;

	pushed_count = 0;
	while (stack->a->size > 0)
	{
		if (get_value(stack->a->head) <= pushed_count)
		{
			pb(stack, 1);
			rb(stack, 1);
			pushed_count++;
		}
		else if (get_value(stack->a->head) <= pushed_count + chunk_size)
		{
			pb(stack, 1);
			pushed_count++;
		}
		else
			ra(stack, 1);
	}
}

static void	phase_pull_b_to_a(t_stack *stack, int size)
{
	while (size > 0)
	{
		move_to_top_b(stack, find_position(stack->b, size - 1));
		pa(stack, 1);
		size--;
	}
}

static void	bring_min_to_top_and_pb(t_stack *stack)
{
	int pos;
	int size;

	if (!stack || !stack->a)
		return ;
	size = (int)stack->a->size;
	pos = find_position(stack->a, find_min_value(stack->a));
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(stack, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rra(stack, 1);
	}
	pb(stack, 1);
}

void	sort_many(t_stack *stack)
{
	int		size;
	int		chunks;
	int		chunk_size;

	size = stack->a->size;
	if (size == 4)
	{
		bring_min_to_top_and_pb(stack);
		sort_3(stack);
		pa(stack, 1);
		return ;
	}
	if (size == 5)
	{
		bring_min_to_top_and_pb(stack);
		bring_min_to_top_and_pb(stack);
		sort_3(stack);
		pa(stack, 1);
		pa(stack, 1);
		return ;
	}
	if (size <= 100)
		chunks = 5;
	else
		chunks = 11;
	chunk_size = size / chunks;
	phase_push_a_to_b(stack, chunk_size);
	phase_pull_b_to_a(stack, size);
}
