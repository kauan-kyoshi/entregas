/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:56:21 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 12:48:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_init_part(t_table *table, int forks_inited,
int inited_flags, t_philo *philos)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < forks_inited)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (inited_flags & 1)
		pthread_mutex_destroy(&table->print_mutex);
	if (inited_flags & 2)
		pthread_mutex_destroy(&table->state_mutex);
	if (philos)
		free(philos);
}

static void	init_philos(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % table->n_philo;
		philos[i].meals = 0;
		philos[i].last_meal = 0;
		philos[i].thread = 0;
		philos[i].table = table;
		i++;
	}
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			clean_init_part(table, i, 0, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutexes(t_table *table)
{
	if (!init_forks(table))
		return (0);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		clean_init_part(table, table->n_philo, 0, NULL);
		return (0);
	}
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
	{
		clean_init_part(table, table->n_philo, 1, NULL);
		return (0);
	}
	return (1);
}

int	init_table(t_args *args, t_table *table, t_philo **philos)
{
	if (!args || !table || !philos)
		return (0);
	table->n_philo = args->n_philo;
	table->time_sleep = args->time_sleep;
	table->time_die = args->time_die;
	table->time_eat = args->time_eat;
	table->must_eat = args->must_eat;
	if (!init_mutexes(table))
		return (0);
	*philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!*philos)
	{
		clean_init_part(table, table->n_philo, 3, NULL);
		return (0);
	}
	init_philos(table, *philos);
	table->start_time = 0;
	table->stop = 0;
	table->finished_count = 0;
	return (1);
}
