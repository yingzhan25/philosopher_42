/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:58:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/13 17:53:19 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Different strategy for even and odd philo to avoid deadlock;
 * Return the fork already took if is died when waiting for another
 * fork or before eating;
 * Only 1 philo: return immediately and the monitor waits for its death
 */
static int	take_fork_up(t_philo *p)
{
	if (p->id % 2 == 1)
	{
		pthread_mutex_lock(&p->data->fork[p->right_fork]);
		print_safe(p, p->id, "takes a fork");
		if (p->data->num_of_philo == 1 || read_stop(p->data))
			return (pthread_mutex_unlock(&p->data->fork[p->right_fork]), 1);
		pthread_mutex_lock(&p->data->fork[p->left_fork]);
		print_safe(p, p->id, "takes a fork");
		if (read_stop(p->data))
			return (pthread_mutex_unlock(&p->data->fork[p->right_fork]), \
			pthread_mutex_unlock(&p->data->fork[p->left_fork]), 1);
	}
	else
	{
		pthread_mutex_lock(&p->data->fork[p->left_fork]);
		print_safe(p, p->id, "takes a fork");
		if (read_stop(p->data))
			return (pthread_mutex_unlock(&p->data->fork[p->left_fork]), 1);
		pthread_mutex_lock(&p->data->fork[p->right_fork]);
		print_safe(p, p->id, "takes a fork");
		if (read_stop(p->data))
			return (pthread_mutex_unlock(&p->data->fork[p->left_fork]), \
			pthread_mutex_unlock(&p->data->fork[p->right_fork]), 1);
	}
	return (0);
}

static void	put_fork_down(t_philo *p)
{
	if (p->id % 2 == 1)
	{
		pthread_mutex_unlock(&p->data->fork[p->right_fork]);
		print_safe(p, p->id, "puts down a fork");
		pthread_mutex_unlock(&p->data->fork[p->left_fork]);
		print_safe(p, p->id, "puts down a fork");
	}
	else
	{
		pthread_mutex_unlock(&p->data->fork[p->left_fork]);
		print_safe(p, p->id, "puts down a fork");
		pthread_mutex_unlock(&p->data->fork[p->right_fork]);
		print_safe(p, p->id, "puts down a fork");
	}
}
/**
 * Make sure thread exits when everyone eat same number of meals;
 * Otherwise monitor can not notice this issue and someone will eat more;
 * Using same time stamp in print function and while loop
 */

static int	eat_with_fork(t_philo *p)
{
	int			ret;
	long long	last_meal;

	if (read_stop(p->data))
		return (1);
	if (is_finish(p))
		return (1);
	ret = take_fork_up(p);
	if (ret)
		return (1);
	last_meal = print_safe(p, p->id, "is eating");
	write_meal_time(p, last_meal);
	write_meal_count(p);
	while (time_stamp(p->data->base_time) < p->last_meal_time + \
		p->data->time_to_eat)
	{
		if (read_stop(p->data))
			return (put_fork_down(p), 1);
		usleep(500);
	}
	put_fork_down(p);
	return (0);
}

/**
 * Return whenever read_stop is true;
 * Sleep in time fragrants to detect death asap
 */
void	*routine(void *arg)
{
	t_philo		*philo;
	long long	start_sleep;

	philo = (t_philo *)arg;
	while (!read_stop(philo->data))
	{
		if (eat_with_fork(philo))
			break ;
		start_sleep = print_safe(philo, philo->id, "is sleeping");
		if (read_stop(philo->data))
			return (NULL);
		while (time_stamp(philo->data->base_time) < start_sleep \
			+ philo->data->time_to_sleep)
		{
			if (read_stop(philo->data))
				return (NULL);
			usleep(500);
		}
		print_safe(philo, philo->id, "is thinking");
	}
	return (NULL);
}
