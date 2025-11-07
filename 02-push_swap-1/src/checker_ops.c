/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:56 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:58:57 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	apply_swap_ops(t_stack *stack, const char *op)
{
	if (!ft_strncmp(op, "sa\n", 3) || !ft_strncmp(op, "sa\0", 3))
		return (sa(stack, 0), 1);
	if (!ft_strncmp(op, "sb\n", 3) || !ft_strncmp(op, "sb\0", 3))
		return (sb(stack, 0), 1);
	if (!ft_strncmp(op, "ss\n", 3) || !ft_strncmp(op, "ss\0", 3))
		return (sa(stack, 0), sb(stack, 0), 1);
	return (0);
}

int	apply_push_ops(t_stack *stack, const char *op)
{
	if (!ft_strncmp(op, "pa\n", 3) || !ft_strncmp(op, "pa\0", 3))
		return (pa(stack, 0), 1);
	if (!ft_strncmp(op, "pb\n", 3) || !ft_strncmp(op, "pb\0", 3))
		return (pb(stack, 0), 1);
	return (0);
}

int	apply_rotate_ops(t_stack *stack, const char *op)
{
	if (!ft_strncmp(op, "ra\n", 3) || !ft_strncmp(op, "ra\0", 3))
		return (ra(stack, 0), 1);
	if (!ft_strncmp(op, "rb\n", 3) || !ft_strncmp(op, "rb\0", 3))
		return (rb(stack, 0), 1);
	if (!ft_strncmp(op, "rr\n", 3) || !ft_strncmp(op, "rr\0", 3))
		return (ra(stack, 0), rb(stack, 0), 1);
	return (0);
}

int	apply_rev_rotate_ops(t_stack *stack, const char *op)
{
	if (!ft_strncmp(op, "rra\n", 4) || !ft_strncmp(op, "rra\0", 4))
		return (rra(stack, 0), 1);
	if (!ft_strncmp(op, "rrb\n", 4) || !ft_strncmp(op, "rrb\0", 4))
		return (rrb(stack, 0), 1);
	if (!ft_strncmp(op, "rrr\n", 4) || !ft_strncmp(op, "rrr\0", 4))
		return (rra(stack, 0), rrb(stack, 0), 1);
	return (0);
}

int	apply_op(t_stack *stack, const char *op)
{
	if (!op)
		return (0);
	if (apply_swap_ops(stack, op))
		return (1);
	if (apply_push_ops(stack, op))
		return (1);
	if (apply_rotate_ops(stack, op))
		return (1);
	if (apply_rev_rotate_ops(stack, op))
		return (1);
	return (0);
}
