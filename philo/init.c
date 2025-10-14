/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:55:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/14 11:58:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	is_validate(char **argv, t_shared *data)
{
	if (!argv[1] || !*argv[1] || !argv[2] || !*argv[2] || !argv[3] || \
		!*argv[3] || !argv[4] || !*argv[4])
		return (printf("Args cannnot be empty\n"), 1);
	if (is_number(argv[1]) || is_number(argv[2]) || is_number(argv[3]) \
		|| is_number(argv[4]))
		return (printf("Args should be positive integer\n"), 1);
	if ((argv[5] && *argv[5]) && is_number(argv[5]))
		return (printf("Args should be positive integer\n"), 1);
	data->num_of_philo = ft_atoi(argv[1]);
	if (data->num_of_philo < MIN_PHILO || data->num_of_philo > MAX_PHILO)
		return (printf("Number of philo is 1-200\n"), 1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < MIN_TIME || data->time_to_die > MAX_TIME)
		return (printf("Time duration is 60-600000ms\n"), 1);
	if (argv[5] && *argv[5])
	{
		data->time_each_need_eat = ft_atoi(argv[5]);
		if (data->time_each_need_eat <= 0 || data->time_each_need_eat > MAX_EAT)
			return (printf("Time need eat is 1-1000\n"), 1);
	}
	else
		data->time_each_need_eat = -1;
	return (0);
}

/**
 * Index of philo array starts from 0, id starts from 1;
 * Using (i + 1) % data->num_of_philo for a ring of forks;
 * Allow philo to access shared data;
 * Also allow data to access philo for conviniece of parameter
 */
static int	init_philo(t_shared *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (1);
	data->thread = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!data->thread)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->fork)
		return (1);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].time_already_eat = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->num_of_philo;
		data->philo[i].data = data;
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (0);
}

/**
 * Check all possible invalid inputs because ft_atoi is unsafe;
 * Data on the stack, Philo on the heap
 */
int	init_data(char **argv, t_shared *data)
{
	struct timeval	tv;

	if (is_validate(argv, data))
		return (1);
	data->is_stop = 0;
	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday"), 1);
	data->base_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->stop, NULL);
	pthread_mutex_init(&data->meal_count, NULL);
	pthread_mutex_init(&data->meal_time, NULL);
	if (init_philo(data))
		return (1);
	return (0);
}
