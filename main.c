# include "philo.h"

int	init_struct(char **argv, t_shared *data)
{
	struct timeval  tv;

	if (!argv[1] | !*argv[1] | !argv[2] | !*argv[2] | !argv[3] | !*argv[3] | !argv[4] | !*argv[4])
		return (1);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] && *argv[5])
		data->time_each_need_eat = ft_atoi(argv[5]);
	else
		data->time_each_need_eat = -1;
	data->is_stop = 0;
	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday"), 1);
	data->base_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->stop, NULL);
	if (init_philo(data))
		return (1);
	return (0);
}

int init_philo(t_shared *data)
{
	int i;

	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (1);
	data->thread = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!data->thread)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->fork)
		return (1);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = -1;
		data->philo[i].time_already_eat = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->num_of_philo;
		pthread_create(&data->thread[i], NULL, routine, &data->philo[i]);
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (0);
}

int should_die(t_philo *philo)
{
//	if (read_stop(philo))
//	return (1);
	if (time_stamp(philo->data->base_time) - philo->last_meal_time > philo->data->time_to_die)
		return (write_stop(philo->data), 1);
//	if (philo->time_already_eat != -1 && philo->time_already_eat >= philo->data->time_each_need_eat)
//	return (write_stop(philo->data), 1);
	return (0);
}

int should_finish(t_philo *philo)
{
//	if (read_stop(philo))
//	return (1);
//	if (time_stamp(philo->data->base_time) - philo->last_meal_time > philo->data->time_to_die)
//	return (write_stop(philo->data), 1);
	if (philo->data->time_each_need_eat != -1 && philo->time_already_eat >= philo->data->time_each_need_eat)
		return (write_stop(philo->data), 1);
	return (0);
}

int	eat_with_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has taken a fork\n");
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has taken a fork\n");

	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has taken a fork\n");
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has taken a fork\n");
	}
	print_safe(philo, philo->last_meal_time, philo->id, " is eating\n");
	philo->time_already_eat++;
	while (time_stamp(philo->data->base_time < philo->last_meal_time + philo->data->time_to_eat))
	{
		usleep(500);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has put down a fork\n");
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has put down a fork\n");

	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has put down a fork\n");
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		print_safe(philo, time_stamp(philo->data->base_time), philo->id, " has put down a fork\n");
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;
	long	start_sleep;
	long	start_think;

	philo = (t_philo*)arg;
	while (!read_stop(philo->data))
	{
		if (eat_with_fork(philo))
			break ;
		start_sleep = time_stamp(philo->data->base_time);
		print_safe(philo, start_sleep, philo->id, " is sleeping\n");
		while (time_stamp(philo->data->base_time) < start_sleep + philo->data->time_to_sleep)
		{
			usleep(500);
		}
		start_think = time_stamp(philo->data->base_time);
		print_safe(philo, start_think, philo->id, " is thinking\n");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_shared	*data;
	int	 i;
	int	 all_finish;

	data = (t_shared*)arg;
	while (!read_stop(data))
	{
		i = 0;
		all_finish = 1;
		while (!read_stop(data) && i < data->num_of_philo)
		{
			if (should_die(&data->philo[i]))
			{
				print_safe(&data->philo[i], time_stamp(data->base_time), data->philo->id, " is died\n");
				//	write_stop(data);
				return (NULL);
			}
			if (data->time_each_need_eat != -1 && !should_finish(&data->philo[i]))
				all_finish = 0;
			i++;
		}
		if (data->time_each_need_eat != -1 && all_finish)
		{
			//	write_stop(data);
			return (NULL);
		}
		usleep(1000);
	}
}

int main(int argc, char *argv[])
{
	t_shared	data;
	pthread_t	m_thread;
	int			i;

	if (argc < 5 | argc > 6)
	{
		printf("number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (init_struct(argv, &data))
	{
		printf("Failed to initialize\n");
		return (0);
	}
	pthread_create(&m_thread, NULL, monitor, &data);
	pthread_join(m_thread, NULL);
	write_stop(&data);
	i = 0;
	while (i < data.num_of_philo)
	{
		pthread_join(data.thread[i], NULL);
		i++;
	}
	free(data.thread);
	free(data.fork);
	free(data.philo);
	pthread_mutex_destroy(&data.stop);
	pthread_mutex_destroy(&data.print);
	return (0);
}