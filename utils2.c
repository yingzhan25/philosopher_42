/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:06:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 12:54:35 by yingzhan         ###   ########.fr       */
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

/**
 * Protect from philo and moninor threads read and write meal_time
 * at the same time
 */
void	write_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_time);
	philo->last_meal_time = time_stamp(philo->data->base_time);
	pthread_mutex_unlock(&philo->data->meal_time);
}

long long	read_meal_time(t_philo *philo)
{
	long long	value;

	pthread_mutex_lock(&philo->data->meal_time);
	value = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_time);
	return (value);
}

/**
 * Protect from philo and moninor threads read and write meal_count
 * at the same time
 */
void	write_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_count);
	philo->time_already_eat++;
	pthread_mutex_unlock(&philo->data->meal_count);
}

int	read_meal_count(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->data->meal_count);
	value = philo->time_already_eat;
	pthread_mutex_unlock(&philo->data->meal_count);
	return (value);
}
