/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:22 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/14 15:04:19 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MIN_PHILO 1
# define MAX_PHILO 200
# define MIN_TIME 60
# define MAX_TIME 600000
# define MAX_EAT 1000

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "type.h"

typedef struct s_shared
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_each_need_eat;
	int					is_stop;
	long long			base_time;
	pthread_mutex_t		stop;
	pthread_mutex_t		print;
	pthread_mutex_t		meal_count;
	pthread_mutex_t		meal_time;
	pthread_mutex_t		*fork;
	t_philo				*philo;
	pthread_t			*thread;
}	t_shared;

typedef struct s_philo
{
	int			id;
	long long	last_meal_time;
	int			time_already_eat;
	int			left_fork;
	int			right_fork;
	t_shared	*data;
}	t_philo;

int			init_data(char **argv, t_shared *data);
void		*routine(void *arg);
void		*monitor(void *arg);
int			ft_atoi(const char *nptr);
long long	time_stamp(long long start);
long long	print_safe(t_philo *p, int id, char *action);
int			read_stop(t_shared *data);
void		write_stop(t_shared *data);
void		write_meal_time(t_philo *philo);
long long	read_meal_time(t_philo *philo);
void		write_meal_count(t_philo *philo);
int			read_meal_count(t_philo *philo);
int			is_finish(t_philo *p);
void		clean_up(t_shared *data);

#endif