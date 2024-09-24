/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 08:49:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 08:50:43 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_input
{
	int				nbr_of_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meals;
	long			start_time;
	int				sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_t		monitor_thread;
}	t_input;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	int				holding_r;
	int				holding_l;
	t_fork			*r_fork;
	t_fork			*l_fork;
	pthread_mutex_t	last_meal_lock;
	pthread_t		philo_thread;
	t_input			*input;
}	t_philo;

// Utils
long	get_time_in_ms(void);
void	ft_usleep(long int time_in_ms);
void	write_state(t_philo *philo, t_input *input, char *str);
long	ft_atoi(const char *str);
int		check_if_num(int argc, char **argv);

// Init
int		init_input(t_input *input, int argc, char **argv);
int		create_philos(t_philo **philos, t_fork **forks, t_input	*input);

// Threads
int		create_threads(t_philo **philos, t_input *input);
int		wait_threads(t_philo **philos, t_input *input);

// Forks
void	check_fork(t_philo *philo, t_input *input, char l_or_r);
void	finished_meal(t_philo *philo, t_input *input);

// Monitor
void	*monitor_routine(void *arg);
int		stop_sim(t_input *input);
int		stop_threads(t_input *input);

#endif
