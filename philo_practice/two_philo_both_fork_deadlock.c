// Two philosophers, two forks (Fork1 and Fork2).
// Erroneous implementation: Both philosophers pick up the left fork first, then the right.
//Philosopher1: lock(Fork1) → lock(Fork2) → Eat → unlock
//Philosopher2: lock(Fork2) → lock(Fork1) → Eat → unlock

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{
	int					is_stop;
	long				base;
	pthread_mutex_t		stop;
	pthread_mutex_t		print;
	pthread_mutex_t		fork[2];
}	t_philo;

long	time_stamp(long start)
{
	struct timeval	current;
	long	stamp;

	if (gettimeofday(&current, NULL))
			return (perror("gettimeofday"), -1);
	stamp = current.tv_sec * 1000 + current.tv_usec / 1000 - start;
	return (stamp);
}

void	print_safe(t_philo *p, long stamp, int id, char *action)
{
	pthread_mutex_lock(&p->print);
	printf("%ldms: philo %d %s\n", stamp, id, action);
	pthread_mutex_unlock(&p->print);
}

int	read_stop(t_philo *p)
{
	int	value;

	pthread_mutex_lock(&p->stop);
	value = p->is_stop;
	pthread_mutex_unlock(&p->stop);
	return (value);
}

void	write_stop(t_philo *p)
{
	pthread_mutex_lock(&p->stop);
	p->is_stop = 1;
	pthread_mutex_unlock(&p->stop);
}

int	eat_with_fork(t_philo *p, int id)
{
	long	start_eat;

	if (id == 1)
	{
		pthread_mutex_lock(&p->fork[0]);
		print_safe(p, time_stamp(p->base), id, "has taken a fork");
		pthread_mutex_lock(&p->fork[1]);
		print_safe(p, time_stamp(p->base), id, "has taken a fork");
	}
	else if (id == 2)
	{
		pthread_mutex_lock(&p->fork[1]);
		print_safe(p, time_stamp(p->base), id, "has taken a fork");
		pthread_mutex_lock(&p->fork[0]);
		print_safe(p, time_stamp(p->base), id, "has taken a fork");
	}
	start_eat = time_stamp(p->base);
	print_safe(p, start_eat, id, "is eating");
	if (read_stop(p))
		return (pthread_mutex_unlock(&p->fork[0]), pthread_mutex_unlock(&p->fork[1]), 1);
	while (time_stamp(p->base) < start_eat + 2000)
	{
		if (read_stop(p))
			return (pthread_mutex_unlock(&p->fork[0]), pthread_mutex_unlock(&p->fork[1]), 1);
		usleep(500);
	}
	print_safe(p, time_stamp(p->base), id, "has put down fork");
	if (id == 1)
	{
		pthread_mutex_unlock(&p->fork[0]);
		pthread_mutex_unlock(&p->fork[1]);
	}
	else if (id == 2)
	{
		pthread_mutex_unlock(&p->fork[1]);
		pthread_mutex_unlock(&p->fork[0]);
	}
	return (0);
}

void	*philo1(void *arg)
{
	long	start_think;
	long	start_sleep;
	t_philo	*p;

	p = (t_philo*)arg;
	while (1)
	{
		if (read_stop(p))
			break ;
		start_think = time_stamp(p->base);
		print_safe(p, start_think, 1, "is thinking");
		if (read_stop(p))
			break ;
		while (time_stamp(p->base) < start_think + 1000)
		{
			if (read_stop(p))
				break ;
			usleep(500);
		}
		if (eat_with_fork(p, 1))
			break ;
		start_sleep = time_stamp(p->base);
		print_safe(p, start_sleep, 1, "is sleeping");
		if (read_stop(p))
			break ;
		while (time_stamp(p->base) < start_sleep + 1000)
		{
			if (read_stop(p))
				break ;
			usleep(500);
		}
	}
	return (NULL);
}

void	*philo2(void *arg)
{
	long	start_think;
	long	start_sleep;
	t_philo	*p;

	p = (t_philo*)arg;
	while (1)
	{
		if (read_stop(p))
			break ;
		start_think = time_stamp(p->base);
		print_safe(p, start_think, 2, "is thinking");
		if (read_stop(p))
			break ;
		while (time_stamp(p->base) < start_think + 2000)
		{
			if (read_stop(p))
				break ;
			usleep(500);
		}
		if (eat_with_fork(p, 2))
			break ;
		start_sleep = time_stamp(p->base);
		print_safe(p, start_sleep, 2, "is sleeping");
		if (read_stop(p))
			break ;
		while (time_stamp(p->base) < start_sleep + 2000)
		{
			if (read_stop(p))
				break ;
			usleep(500);
		}
	}
	return (NULL);
}

int	main(void)
{
	t_philo	p;
	pthread_t	t1;
	pthread_t	t2;
	struct timeval	tv;

	p.is_stop = 0;
	pthread_mutex_init(&p.stop, NULL);
	pthread_mutex_init(&p.print, NULL);
	pthread_mutex_init(&p.fork[0], NULL);
	pthread_mutex_init(&p.fork[1], NULL);
	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday"), -1);
	p.base = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (pthread_create(&t1, NULL, *philo1, &p))
		return (-1);
	if (pthread_create(&t2, NULL, *philo2, &p))
	{
		pthread_join(t1, NULL);
		return (-1);
	}
	while (time_stamp(p.base) < 10000)
		usleep(500);
	write_stop(&p);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&p.stop);
	pthread_mutex_destroy(&p.print);
	pthread_mutex_destroy(&p.fork[0]);
	pthread_mutex_destroy(&p.fork[1]);
	return (0);
}