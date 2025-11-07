/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:45 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->a = ft_create_dlist(NULL);
	stack->b = ft_create_dlist(NULL);
	if (!stack->a || !stack->b)
	{
		if (stack->a)
			ft_clean_dlist(&stack->a, free_int);
		if (stack->b)
			ft_clean_dlist(&stack->b, free_int);
		free(stack);
		return (NULL);
	}
	return (stack);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	if (stack->a)
		ft_clean_dlist(&stack->a, free_int);
	if (stack->b)
		ft_clean_dlist(&stack->b, free_int);
	free(stack);
}
