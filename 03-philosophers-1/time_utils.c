/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:23:19 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/01/19 13:46:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	v;

	if (gettimeofday(&v, NULL) == -1)
		return (-1);
	return ((v.tv_sec * 1000LL) + (v.tv_usec / 1000));
}

void	ft_usleep(long long ms)
{
	long long	end;
	long long	now;
	long long	remaining;

	if (ms <= 0)
		return ;
	now = get_time_ms();
	if (now == -1)
		return ;
	end = now + ms;
	while (1)
	{
		now = get_time_ms();
		if (now == -1 || now >= end)
			break ;
		remaining = end - now;
		if (remaining > 5)
			usleep((remaining - 1) * 1000);
		else
			usleep(100);
	}
}
