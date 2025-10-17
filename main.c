/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:08 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 13:01:50 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initialise all the mutexs before creating threads;
 * check return value of all system functions
 */
int	main(int argc, char *argv[])
{
	t_shared	data;
	pthread_t	m_thread;
	int			i;

	if (argc < 5 || argc > 6 || init_data(argv, &data))
	{
		ft_putstr_fd("Invalid INPUT: 1.number_of_philosophers 2.time_to_die ", STDERR_FILENO);
		ft_putstr_fd("3.time_to_eat 4.time_to_sleep ", STDERR_FILENO);
		ft_putstr_fd("5.[number_of_times_each_philosopher_must_eat]\n", STDERR_FILENO);
		return (1);
	}
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_create(&data.thread[i], NULL, routine, &data.philo[i]))
		{
			ft_putstr_fd("Failed to create philo thread\n", STDERR_FILENO);
			write_stop(&data);
			while (--i >= 0)
			{
				if (pthread_join(data.thread[i], NULL))
					ft_putstr_fd("Failed to join philo thread\n", STDERR_FILENO);
			}
			return (clean_up(&data), 1);
		}
	}
	if (pthread_create(&m_thread, NULL, monitor, &data))
	{
		ft_putstr_fd("Failed to create philo thread\n", STDERR_FILENO);
			write_stop(&data);
		i = -1;
		while (++i < data.num_of_philo)
		{
			if (pthread_join(data.thread[i], NULL))
				ft_putstr_fd("Failed to join philo thread\n", STDERR_FILENO);
		}
		return (clean_up(&data), 1);
	}
	if (pthread_join(m_thread, NULL))
		ft_putstr_fd("Failed to join monitor thread\n", STDERR_FILENO);
	write_stop(&data);
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_join(data.thread[i], NULL))
			ft_putstr_fd("Failed to join philo thread\n", STDERR_FILENO);
	}
	return (clean_up(&data));
}

/*
 * Note: When running under Valgrind, due to performance overhead,
 * time parameters may need adjustment or accept deaths in edge cases.
 * Time control is precise when running directly without Valgrind.
 */