/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:21 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:22 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_first_two(t_dlist *stack)
{
	t_dnode	*first;
	t_dnode	*second;
	void	*temp_data;

	if (!stack || !stack->head || !stack->head->next)
		return ;
	first = stack->head;
	second = first->next;
	temp_data = first->data;
	first->data = second->data;
	second->data = temp_data;
}

void	sa(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	swap_first_two(stack->a);
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	swap_first_two(stack->b);
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack *stack)
{
	sa(stack, 0);
	sb(stack, 0);
	write(1, "ss\n", 3);
}
