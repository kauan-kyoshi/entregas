/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:49 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/07 16:58:50 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../libft/get_next_line.h"

int	apply_op(t_stack *stack, const char *op);

static int	run_checker(t_stack *stack)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(0);
	while (line)
	{
		if (!apply_op(stack, line))
			return (free(line), -1);
		count++;
		free(line);
		line = get_next_line(0);
	}
	return (count);
}

int	main(int argc, char **argv)
{
	t_stack	*stack;
	int		ops_count;

	if (argc < 2)
		return (0);
	stack = init_stack();
	if (!stack)
		return (write(2, "Error\n", 6), 1);
	if (!parse_arguments(argc, argv, stack))
		return (free_stack(stack), write(2, "Error\n", 6), 1);
	ops_count = run_checker(stack);
	if (ops_count < 0)
		return (free_stack(stack), write(2, "Error\n", 6), 1);
	if (is_sorted(stack->a) && (!stack->b || stack->b->size == 0))
		ft_printf("OK (ops=%d)\n", ops_count);
	else
		ft_printf("KO (ops=%d)\n", ops_count);
	free_stack(stack);
	return (0);
}
