/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:13 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:14 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push_from_to(t_dlist *from, t_dlist *to)
{
	int	*value_copy;

	if (!from || !to || !from->head)
		return ;
	if (!copy_top_value(from, &value_copy))
		return ;
	detach_head_node(from);
	push_value_to_dest(to, value_copy);
}

void	pa(t_stack *stack, int print)
{
	if (!stack || !stack->b || !stack->b->head)
		return ;
	push_from_to(stack->b, stack->a);
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack *stack, int print)
{
	if (!stack || !stack->a || !stack->a->head)
		return ;
	push_from_to(stack->a, stack->b);
	if (print)
		write(1, "pb\n", 3);
}
