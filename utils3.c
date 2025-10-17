/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:10:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 12:43:57 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
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

int	is_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (len > MAX_DIGIT)
			return (1);
		len++;
	}
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

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s == NULL || fd < 0)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}