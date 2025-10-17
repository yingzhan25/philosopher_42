/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:06:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 13:10:56 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_up(t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (destroy_single_mutex(&data->fork[i]))
			return (1);
		i++;
	}
	if (destroy_single_mutex(&data->stop) || destroy_single_mutex(&data->print) || destroy_single_mutex(&data->meal_count) || destroy_single_mutex(&data->meal_time))
		return (1);
	free(data->thread);
	free(data->fork);
	free(data->philo);
	return (0);
}

int	destroy_single_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		return (ft_putstr_fd("Failed mutex destroy\n", STDERR_FILENO), 1);
	return (0);
}

int	destroy_fork_mutex(t_shared *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (destroy_single_mutex(&data->fork[i]))
			return (1);
		j++;
	}
	free(data->thread);
	free(data->fork);
	free(data->philo);
	return (0);
}
