/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:38:51 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/20 16:40:59 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9' );
}

static int	parse_positive_int(const char *str, int *out)
{
	long	result;
	int		i;

	if (!str || !str[0])
		return (0);
	i = 0;
	result = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	if (result <= 0)
		return (0);
	*out = (int)result;
	return (1);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (!parse_positive_int(argv[1], &args->n_philo))
		return (0);
	if (!parse_positive_int(argv[2], &args->time_die))
		return (0);
	if (!parse_positive_int(argv[3], &args->time_eat))
		return (0);
	if (!parse_positive_int(argv[4], &args->time_sleep))
		return (0);
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5], &args->must_eat))
			return (0);
	}
	else
		args->must_eat = -1;
	return (1);
}
