/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:08 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/16 11:47:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("Invalid INPUT: 1.number_of_philosophers 2.time_to_die ");
		printf("3.time_to_eat 4.time_to_sleep ");
		printf("5.[number_of_times_each_philosopher_must_eat]\n");
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