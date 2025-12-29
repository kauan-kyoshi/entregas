/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:03:05 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 12:48:26 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_finished(t_table *table)
{
	if (table->must_eat > 0 && table->finished_count >= table->n_philo)
	{
		table->stop = 1;
		return (1);
	}
	return (0);
}

static int	handle_death(t_table *table, t_philo *philo, long long now,
long long last)
{
	if ((now - last) > table->time_die)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (!table->stop)
		{
			table->stop = 1;
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld %d died\n", now - table->start_time, philo->id);
			pthread_mutex_unlock(&table->print_mutex);
		}
		pthread_mutex_unlock(&table->state_mutex);
		return (1);
	}
	return (0);
}

static int	check_philos(t_philo *philos)
{
	t_table		*table;
	int			i;
	long long	now;
	long long	last;

	table = philos[0].table;
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->stop)
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (1);
		}
		last = philos[i].last_meal;
		pthread_mutex_unlock(&table->state_mutex);
		now = get_time_ms();
		if (now == -1)
			return (1);
		if (handle_death(table, &philos[i], now, last))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_table	*table;

	if (!arg)
		return (NULL);
	philos = (t_philo *)arg;
	table = philos[0].table;
	while (1)
	{
		if (check_philos(philos))
			return (NULL);
		pthread_mutex_lock(&table->state_mutex);
		if (check_finished(table))
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(500);
	}
	return (NULL);
}
