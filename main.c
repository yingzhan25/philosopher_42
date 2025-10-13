/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:08 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/13 18:16:30 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	init_data(char **argv, t_shared *data)
{
	struct timeval	tv;

	if (!argv[1] || !*argv[1] || !argv[2] || !*argv[2] || !argv[3] || \
		!*argv[3] || !argv[4] || !*argv[4])
		return (1);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] && *argv[5])
		data->time_each_need_eat = ft_atoi(argv[5]);
	else
		data->time_each_need_eat = -1;
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

/**
 * Initialise all the mutexs before creating threads
 */
int	main(int argc, char *argv[])
{
	t_shared	data;
	pthread_t	m_thread;
	int			i;

	if (argc < 5 || argc > 6 || init_data(argv, &data))
	{
		printf("Failed to initialize: number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = -1;
	while (++i < data.num_of_philo)
		pthread_create(&data.thread[i], NULL, routine, &data.philo[i]);
	pthread_create(&m_thread, NULL, monitor, &data);
	pthread_join(m_thread, NULL);
	write_stop(&data);
	i = -1;
	while (++i < data.num_of_philo)
		pthread_join(data.thread[i], NULL);
	clean_up(&data);
	return (0);
}

/*
 * Note: When running under Valgrind, due to performance overhead,
 * time parameters may need adjustment or accept deaths in edge cases.
 * Time control is precise when running directly without Valgrind.
 */