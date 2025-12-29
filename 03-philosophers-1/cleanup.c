/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:49:37 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 11:46:57 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table(t_table *table, t_philo *philos)
{
	int		i;

	if (!table)
		return ;
	if (table->forks)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->state_mutex);
	if (philos)
		free(philos);
}
