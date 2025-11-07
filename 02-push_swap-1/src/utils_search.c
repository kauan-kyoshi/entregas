/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 17:00:01 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_min_value(t_dlist *stack)
{
	t_dnode	*current;
	int		min;

	if (!stack || !stack->head)
		return (0);
	min = get_value(stack->head);
	current = stack->head->next;
	while (current)
	{
		if (get_value(current) < min)
			min = get_value(current);
		current = current->next;
	}
	return (min);
}

int	find_max_value(t_dlist *stack)
{
	t_dnode	*current;
	int		max;

	if (!stack || !stack->head)
		return (0);
	max = get_value(stack->head);
	current = stack->head->next;
	while (current)
	{
		if (get_value(current) > max)
			max = get_value(current);
		current = current->next;
	}
	return (max);
}

int	find_position(t_dlist *stack, int value)
{
	t_dnode	*current;
	int		pos;

	if (!stack || !stack->head)
		return (-1);
	current = stack->head;
	pos = 0;
	while (current)
	{
		if (get_value(current) == value)
			return (pos);
		current = current->next;
		pos++;
	}
	return (-1);
}

int	distance_to_top(t_dlist *stack, int position)
{
	if (position < 0 || !stack)
		return (0);
	if (position <= (int)stack->size / 2)
		return (position);
	else
		return ((int)stack->size - position);
}
