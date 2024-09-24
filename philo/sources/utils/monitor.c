/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 14:04:06 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 08:43:36 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	all_full(t_philo **philos, t_input *input)
{
	int	all_full;
	int	count;
	int	i;

	all_full = false;
	count = 0;
	i = 0;
	while (i < input->nbr_of_philos)
	{
		pthread_mutex_lock(&(input->eat_lock));
		if ((*philos)[i].meals_eaten >= input->max_meals)
		{
			if (input->max_meals != -1)
				count++;
		}
		pthread_mutex_unlock(&(input->eat_lock));
		i++;
	}
	if (count == input->nbr_of_philos)
		all_full = true;
	return (all_full);
}

static int	dead_philo(t_philo *philo, t_input *input, long cur_time)
{
	int	dead;
	int	last_meal;

	dead = false;
	pthread_mutex_lock(&(philo->last_meal_lock));
	last_meal = cur_time - philo->last_meal;
	pthread_mutex_unlock(&(philo->last_meal_lock));
	if (last_meal > input->tt_die)
	{
		pthread_mutex_lock(&(input->print_lock));
		pthread_mutex_lock(&(input->sim_stop_lock));
		input->sim_stop = true;
		pthread_mutex_unlock(&(input->sim_stop_lock));
		printf("%09ld %d died\n", cur_time, philo->id + 1);
		pthread_mutex_unlock(&(input->print_lock));
		dead = true;
	}
	return (dead);
}

void	*monitor_routine(void *arg)
{
	t_input		*input;
	t_philo		**philos;
	long		cur_time;
	int			cur;

	philos = (t_philo **)arg;
	input = philos[0]->input;
	while (1)
	{
		cur = 0;
		cur_time = get_time_in_ms() - input->start_time;
		while (cur < input->nbr_of_philos)
		{
			if (dead_philo(&(*philos)[cur], input, cur_time) == true)
				return (NULL);
			cur++;
		}
		if (all_full(philos, input) == true)
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}

int	stop_sim(t_input *input)
{
	int	state;

	pthread_mutex_lock(&(input->sim_stop_lock));
	state = input->sim_stop;
	pthread_mutex_unlock(&(input->sim_stop_lock));
	return (state);
}

int	stop_threads(t_input *input)
{
	pthread_mutex_lock(&(input->sim_stop_lock));
	input->sim_stop = true;
	pthread_mutex_unlock(&(input->sim_stop_lock));
	return (EXIT_FAILURE);
}
