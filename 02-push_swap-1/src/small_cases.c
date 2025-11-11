#include "../includes/push_swap.h"

void	bring_min_to_top_and_pb(t_stack *stack)
{
    int	pos;
    int	size;

    if (!stack || !stack->a)
        return ;
    size = (int)stack->a->size;
    pos = find_position(stack->a, find_min_value(stack->a));
    if (pos <= size / 2)
    {
        while (pos-- > 0)
            ra(stack, 1);
    }
    else
    {
        pos = size - pos;
        while (pos-- > 0)
            rra(stack, 1);
    }
    pb(stack, 1);
}

int	handle_small_cases(t_stack *stack, int size)
{
    if (size == 4)
    {
        bring_min_to_top_and_pb(stack);
        sort_3(stack);
        pa(stack, 1);
        return (1);
    }
    if (size == 5)
    {
        bring_min_to_top_and_pb(stack);
        bring_min_to_top_and_pb(stack);
        sort_3(stack);
        pa(stack, 1);
        pa(stack, 1);
        return (1);
    }
    return (0);
}