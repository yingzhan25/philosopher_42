/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:09:33 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/14 14:46:29 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * nb);
}

/**
 * Return relative time based on the start time of the program
 */
long long	time_stamp(long long start)
{
	struct timeval	current;
	long long		stamp;

	if (gettimeofday(&current, NULL))
		return (perror("gettimeofday"), -1);
	stamp = current.tv_sec * 1000 + current.tv_usec / 1000 - start;
	return (stamp);
}

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
