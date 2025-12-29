/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:02:57 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/28 23:02:59 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->state_mutex);
	stopped = table->stop;
	pthread_mutex_unlock(&table->state_mutex);
	return (stopped);
}

void	print_status(t_philo *philo, const char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->table->state_mutex);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->state_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->table->print_mutex);
	now = get_time_ms() - philo->table->start_time;
	printf("%lld %d %s\n", now, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
	pthread_mutex_unlock(&philo->table->state_mutex);
}
