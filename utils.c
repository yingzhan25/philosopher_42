# include "philo.h"

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

long	time_stamp(long start)
{
	struct timeval	current;
	long	stamp;

	if (gettimeofday(&current, NULL))
			return (perror("gettimeofday"), -1);
	stamp = current.tv_sec * 1000 + current.tv_usec / 1000 - start;
	return (stamp);
}

void	print_safe(t_philo *philo, long stamp, int id, char *action)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ldms: philo %d %s\n", stamp, id, action);
	pthread_mutex_unlock(&philo->data->print);
}

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