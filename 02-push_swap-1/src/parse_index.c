/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:27 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:28 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	bubble_sort(int *arr, int n)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	*build_sorted_array(t_dlist *a)
{
	int		*sorted_arr;
	int		i;
	t_dnode	*current;

	sorted_arr = malloc(sizeof(int) * a->size);
	if (!sorted_arr)
		return (NULL);
	current = a->head;
	i = 0;
	while (current)
	{
		sorted_arr[i++] = get_value(current);
		current = current->next;
	}
	bubble_sort(sorted_arr, a->size);
	return (sorted_arr);
}

static void	assign_indices(t_dlist *a, int *sorted_arr)
{
	t_dnode	*current;
	int		j;

	current = a->head;
	while (current)
	{
		j = 0;
		while (j < (int)a->size)
		{
			if (get_value(current) == sorted_arr[j])
			{
				*((int *)current->data) = j;
				break ;
			}
			j++;
		}
		current = current->next;
	}
}

void	ps_index_stack(t_stack *stack)
{
	int	*sorted_arr;

	sorted_arr = build_sorted_array(stack->a);
	if (!sorted_arr)
		return ;
	assign_indices(stack->a, sorted_arr);
	free(sorted_arr);
}
