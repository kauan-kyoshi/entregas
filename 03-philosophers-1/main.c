/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:41:10 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 12:41:58 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_start_and_last_meal(t_table *table, t_philo *philos)
{
	int	i;

	table->start_time = get_time_ms();
	if (table->start_time == -1)
		return (0);
	i = 0;
	while (i < table->n_philo)
	{
		philos[i].last_meal = table->start_time;
		i++;
	}
	return (1);
}

static int	start_threads_and_monitor(t_table *table, t_philo *philos,
pthread_t *monitor)
{
	if (create_thread(table, philos) != 0)
		return (0);
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
	{
		table->stop = 1;
		join_threads(table, philos);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_table		table;
	t_philo		*philos;
	pthread_t	monitor;

	if (!parse_args(argc, argv, &args))
		return (1);
	if (!init_table(&args, &table, &philos))
		return (1);
	if (!set_start_and_last_meal(&table, philos))
	{
		destroy_table(&table, philos);
		return (1);
	}
	if (!start_threads_and_monitor(&table, philos, &monitor))
	{
		destroy_table(&table, philos);
		return (1);
	}
	pthread_join(monitor, NULL);
	join_threads(&table, philos);
	destroy_table(&table, philos);
	return (0);
}
