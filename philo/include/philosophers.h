/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 08:49:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/10 14:52:41 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock_mutex;
}	t_fork;

typedef struct s_input
{
	int				nbr_of_philos;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	int				max_meals;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		death_thread;
}	t_input;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	int				l_taken;
	int				r_taken;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread;
	t_input			*input;
}	t_philo;

// Utils
long	get_timestamp(void);
void	ft_usleep(long time_in_ms);
long	ft_atoi(const char *str);
int		check_if_num(int argc, char **argv);
int		init_input(t_input *input, int argc, char **argv);
int		create_philos(t_philo **philos, t_fork **forks, t_input *input);

#endif