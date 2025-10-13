/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:03:03 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/13 17:50:17 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * One of philos is died
 */
static int	is_die(t_philo *p)
{
	if (time_stamp(p->data->base_time) - read_meal_time(p) > \
		p->data->time_to_die)
		return (1);
	return (0);
}

/**
 * One of philos is full
 */
int	is_finish(t_philo *p)
{
	if (p->data->time_each_need_eat != -1 && \
		read_meal_count(p) >= p->data->time_each_need_eat)
		return (1);
	return (0);
}

/**
 * Write stop when one of philos is died or everyone is full
 */
void	*monitor(void *arg)
{
	t_shared	*data;
	int			i;
	int			all_finish;

	data = (t_shared *)arg;
	while (!read_stop(data))
	{
		i = -1;
		all_finish = 1;
		while (!read_stop(data) && ++i < data->num_of_philo)
		{
			if (is_die(&data->philo[i]))
			{
				print_safe(&data->philo[i], data->philo[i].id, "is died");
				return (write_stop(data), NULL);
			}
			if (data->time_each_need_eat != -1 && !is_finish(&data->philo[i]))
				all_finish = 0;
		}
		if (data->time_each_need_eat != -1 && all_finish)
			return (write_stop(data), NULL);
		usleep(500);
	}
	return (NULL);
}
