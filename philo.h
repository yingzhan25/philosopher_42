#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
    int     id;
    int     last_meal_time;
    int     time_already_eat;
    int     left_fork;
    int     right_fork;
    t_shared    *data;
}	t_philo;

typedef struct s_shared
{
    int                 num_of_philo;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 time_each_need_eat;
    int					is_stop;
	long				base_time;
	pthread_mutex_t		stop;
	pthread_mutex_t		print;
	pthread_mutex_t		*fork;
    t_philo             *philo;
    pthread_t           *thread;
}   t_shared;

int	    ft_atoi(const char *nptr);
long	time_stamp(long start);
void	print_safe(t_philo *p, long stamp, int id, char *action);
int	    read_stop(t_shared *data);
void	write_stop(t_shared *data);


#endif