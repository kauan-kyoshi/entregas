/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_many.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:36 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 16:03:22 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	phase_push_a_to_b(t_stack *stack, int chunk_size)
{
    int	pushed_count;

    pushed_count = 0;
    while (stack->a->size > 0)
    {
        if (get_value(stack->a->head) <= pushed_count)
        {
            pb(stack, 1);
            rb(stack, 1);
            pushed_count++;
        }
        else if (get_value(stack->a->head) <= pushed_count + chunk_size)
        {
            pb(stack, 1);
            pushed_count++;
        }
        else
            ra(stack, 1);
    }
}

void	sort_many(t_stack *stack)
{
    int		size;
    int		chunks;
    int		chunk_size;

    size = stack->a->size;
    if (handle_small_cases(stack, size))
        return ;
    if (size <= 100)
        chunks = 5;
    else
        chunks = 11;
    chunk_size = size / chunks;
    phase_push_a_to_b(stack, chunk_size);
    phase_pull_b_to_a(stack, size);
}