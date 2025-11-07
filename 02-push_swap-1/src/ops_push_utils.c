/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:05 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:06 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	copy_top_value(t_dlist *from, int **out)
{
	int	*value_copy;

	value_copy = malloc(sizeof(int));
	if (!value_copy)
		return (0);
	*value_copy = *((int *)(from->head->data));
	*out = value_copy;
	return (1);
}

void	detach_head_node(t_dlist *from)
{
	t_dnode	*node;

	node = from->head;
	if (from->head == from->tail)
	{
		from->head = NULL;
		from->tail = NULL;
		from->size = 0;
	}
	else
	{
		from->head = from->head->next;
		if (from->head)
			from->head->prev = NULL;
		from->size--;
	}
	free_int(node->data);
	free(node);
}

void	push_value_to_dest(t_dlist *to, int *value_copy)
{
	if (to->head == NULL)
	{
		to->head = ft_create_dnode(value_copy);
		to->tail = to->head;
		to->size = 1;
	}
	else
		ft_push_beg_dlist(to, value_copy);
}
