/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/17 18:37:09 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	t_dlist	*a;
	t_dlist	*b;
}	t_stack;

/* Parsing e validação */
int		parse_arguments(int argc, char **argv, t_stack *stack);
int		is_valid_number(char *str);
int		has_duplicates(int *arr, int size);
void	free_split(char **split);
long	ft_atol(const char *str);

/* Helpers de parsing internos */
int		ps_count_words(char const *s, char c);
int		ps_process_single_arg(char *arg, t_stack *stack);
int		ps_check_duplicates_in_stack(t_dlist *stack);
void	ps_index_stack(t_stack *stack);

/* Inicialização e limpeza */
t_stack	*init_stack(void);
void	free_stack(t_stack *stack);
void	free_int(void *data);

/* Operações básicas */
void	sa(t_stack *stack, int print);
void	sb(t_stack *stack, int print);
void	ss(t_stack *stack);
void	pa(t_stack *stack, int print);
void	pb(t_stack *stack, int print);
void	ra(t_stack *stack, int print);
void	rb(t_stack *stack, int print);
void	rr(t_stack *stack);
void	rra(t_stack *stack, int print);
void	rrb(t_stack *stack, int print);
void	rrr(t_stack *stack);

/* Helpers de push internos */
int		copy_top_value(t_dlist *from, int **out);
void	detach_head_node(t_dlist *from);
void	push_value_to_dest(t_dlist *to, int *value_copy);

/* Funções auxiliares */
int		is_sorted(t_dlist *stack);
int		get_value(t_dnode *node);
int		find_min_value(t_dlist *stack);
int		find_max_value(t_dlist *stack);
int		find_position(t_dlist *stack, int value);
int		distance_to_top(t_dlist *stack, int position);

/* Algoritmos de ordenação */
void	sort_stack(t_stack *stack);
void	sort_2(t_stack *stack);
void	sort_3(t_stack *stack);
void	sort_many(t_stack *stack);

/* Checker helpers */
int		apply_op(t_stack *stack, const char *op);

#endif