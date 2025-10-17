/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:33 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 13:10:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Print msg and return the time stamp for further use;
 * get stamp inside the mutex to avoid time mixing up;
 * when stop-condition activated, it will go through the code but not print
 */
long long	print_safe(t_philo *philo, int id, char *action)
{
	long long	stamp;

	stamp = 0;
	pthread_mutex_lock(&philo->data->print);
	if (!read_stop(philo->data))
	{
		stamp = time_stamp(philo->data->base_time);
		printf("%lldms: philo %d %s\n", stamp, id, action);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (stamp);
}
/**
 * Protect from philo and moninor threads read and write stop-sign
 * at the same time
 */

int	read_stop(t_shared *data)
{
	int	value;

	pthread_mutex_lock(&data->stop);
	value = data->is_stop;
	pthread_mutex_unlock(&data->stop);
	return (value);
}

void	write_stop(t_shared *data)
{
	pthread_mutex_lock(&data->stop);
	data->is_stop = 1;
	pthread_mutex_unlock(&data->stop);
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
