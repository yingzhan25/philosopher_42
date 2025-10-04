#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

long	time_stamp(long start)
{
	struct timeval	current;
	long	stamp;

	if (gettimeofday(&current, NULL))
			return (perror("gettimeofday"), -1);
	stamp = current.tv_sec * 1000 + current.tv_usec / 1000 - start;
	return (stamp);
}

int	main(void)
{
	struct timeval	start;
	int		i;
	long	start_program;
	long	start_think;
	long	start_eat;
	long	start_sleep;

	i = 0;
	if (gettimeofday(&start, NULL))
			return (perror("gettimeofday"), -1);
	start_program = start.tv_sec * 1000 + start.tv_usec / 1000;
	while (i < 5)
	{
		start_think = time_stamp(start_program);
		printf("%ldms: philo 1 is thinking\n", start_think);
		while (time_stamp(start_program) < start_think + 2000)
			usleep(500);
		printf("%ldms: philo 1 has taken a fork\n", time_stamp(start_program));
		start_eat = time_stamp(start_program);
		printf("%ldms: philo 1 is eating\n", start_eat);
		while (time_stamp(start_program) < start_eat + 3000)
			usleep(500);
		printf("%ldms: philo 1 has put down fork\n", time_stamp(start_program));
		start_sleep = time_stamp(start_program);
		printf("%ldms: philo 1 is sleeping\n", start_sleep);
		while (time_stamp(start_program) < start_sleep + 2000)
			usleep(500);
		i++;
	}
	return (0);
}