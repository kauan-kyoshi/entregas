/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:18 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:19 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	rotate_up(t_dlist *stack)
{
	t_dnode	*first;

	if (!stack || !stack->head || stack->size < 2)
		return ;
	first = stack->head;
	stack->head = first->next;
	stack->head->prev = NULL;
	first->next = NULL;
	first->prev = stack->tail;
	stack->tail->next = first;
	stack->tail = first;
}

void	ra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	rotate_up(stack->a);
	if (print)
		write(1, "ra\n", 3);
}

void	rb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	rotate_up(stack->b);
	if (print)
		write(1, "rb\n", 3);
}

void	rr(t_stack *stack)
{
	ra(stack, 0);
	rb(stack, 0);
	write(1, "rr\n", 3);
}
