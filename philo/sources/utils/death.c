/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 14:04:06 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/10 14:46:36 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	is_dead(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&(philo->input->is_dead_mutex));
	state = philo->input->is_dead;
	pthread_mutex_unlock(&(philo->input->is_dead_mutex));
	return (state);
}

int	stop_threads(t_philo *philo)
{
	pthread_mutex_lock(&(philo->input->is_dead_mutex));
	philo->input->is_dead = 1;
	pthread_mutex_unlock(&(philo->input->is_dead_mutex));
	return (1);
}

int	check_philo_death(t_philo *philo, long cur_time)
{
	int	dead;
	int	last_meal;

	dead = false;
	pthread_mutex_lock(&(philo->last_meal_mutex));
	last_meal = cur_time - philo->last_meal;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	if (last_meal > philo->input->tt_die)
	{
		pthread_mutex_lock(&(philo->input->print_mutex));
		pthread_mutex_lock(&(philo->input->is_dead_mutex));
		philo->input->is_dead = 1;
		pthread_mutex_unlock(&(philo->input->is_dead_mutex));
		printf("%ld %d died\n", cur_time, philo->id);
		pthread_mutex_lock(&(philo->input->print_mutex));
		dead = true;
	}
	return (dead);
}

void	*monitor_routine(void *arg)
{
	t_input	*input;
	t_philo	**philos;
	long	cur_time;
	int		i;

	philos = (t_philo **)arg;
	input = philos[0]->input;
	while (1)
	{
		i = 0;
		cur_time = get_timestamp() - input->start_time;
		while (i < input->nbr_of_philos)
		{
			
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
