/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:16 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:17 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	rotate_down(t_dlist *stack)
{
	t_dnode	*last;

	if (!stack || !stack->tail || stack->size < 2)
		return ;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->prev = NULL;
	last->next = stack->head;
	stack->head->prev = last;
	stack->head = last;
}

void	rra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	rotate_down(stack->a);
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	rotate_down(stack->b);
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack *stack)
{
	rra(stack, 0);
	rrb(stack, 0);
	write(1, "rrr\n", 4);
}
