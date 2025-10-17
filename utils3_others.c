/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:10:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/10/17 13:11:05 by yingzhan         ###   ########.fr       */
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