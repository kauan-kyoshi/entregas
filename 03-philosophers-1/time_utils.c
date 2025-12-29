/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:23:19 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/20 16:38:33 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long ms)
{
	long long	start;
	long long	now;

	if (ms <= 0)
		return ;
	start = get_time_ms();
	if (start == -1)
		return ;
	while (1)
	{
		now = get_time_ms();
		if (now == -1)
			return ;
		if ((now - start) >= ms)
			break ;
		usleep(500);
	}
}
