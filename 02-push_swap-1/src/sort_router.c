/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:39 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:59:40 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_stack(t_stack *stack)
{
	if (!stack || !stack->a || is_sorted(stack->a))
		return ;
	if (stack->a->size == 2)
		sort_2(stack);
	else if (stack->a->size == 3)
		sort_3(stack);
	else
		sort_many(stack);
}
