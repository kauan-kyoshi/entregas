/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:48 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:49 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	has_duplicates(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_sorted(t_dlist *stack)
{
	t_dnode	*current;

	if (!stack || !stack->head || stack->size < 2)
		return (1);
	current = stack->head;
	while (current && current->next)
	{
		if (get_value(current) > get_value(current->next))
			return (0);
		current = current->next;
	}
	return (1);
}
