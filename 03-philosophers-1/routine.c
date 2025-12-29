/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 22:19:28 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/28 23:01:24 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_status(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	int	is_single;

	is_single = (philo->table->n_philo == 1);
	take_forks(philo);
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal = get_time_ms();
	philo->meals++;
	if (philo->table->must_eat > 0
		&& philo->meals == philo->table->must_eat)
		philo->table->finished_count++;
	pthread_mutex_unlock(&philo->table->state_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_eat);
	if (is_single)
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		pthread_mutex_unlock(&philo->table->forks[philo->right]);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->table->time_die);
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		ft_usleep(1);
	while (!sim_stopped(philo->table))
	{
		eat(philo);
		if (sim_stopped(philo->table))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	create_thread(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			while (i-- > 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
