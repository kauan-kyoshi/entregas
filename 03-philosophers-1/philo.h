/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:31:40 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/01/19 13:46:34 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	long long		start_time;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				stop;
	int				finished_count;
}	t_table;

typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	int			meals;
	long long	last_meal;
	pthread_t	thread;
	t_table		*table;
}	t_philo;

typedef struct s_arg
{
	int	n_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}	t_args;

int			parse_args(int argc, char **argv, t_args *args);

long long	get_time_ms(void);
void		ft_usleep(long long ms);

int			init_table(t_args *args, t_table *table, t_philo **philos);
void		destroy_table(t_table *table, t_philo *philos);

int			create_thread(t_table *table, t_philo *philos);
void		join_threads(t_table *table, t_philo *philos);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);

int			sim_stopped(t_table *table);
void		print_status(t_philo *philo, const char *msg);

#endif