/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 13:24:47 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 08:50:33 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

static void	start_meal(t_philo *philo, t_input *input)
{
	write_state(philo, input, "is eating");
	ft_usleep(input->tt_eat);
	pthread_mutex_lock(&(input->eat_lock));
	philo->meals_eaten++;
	pthread_mutex_unlock(&(input->eat_lock));
	pthread_mutex_lock(&(philo->last_meal_lock));
	philo->last_meal = get_time_in_ms() - input->start_time;
	pthread_mutex_unlock(&(philo->last_meal_lock));
	finished_meal(philo, input);
}

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_input		*input;

	philo = (t_philo *)arg;
	input = philo->input;
	if (philo->id % 2 != 0)
	{
		write_state(philo, input, "is thinking");
		ft_usleep(input->tt_eat);
	}
	while (stop_sim(input) == false)
	{
		if (philo->meals_eaten >= input->max_meals
			&& input->max_meals > 0)
			break ;
		check_fork(philo, input, 'l');
		if (philo->holding_l == true)
			check_fork(philo, input, 'r');
		if (philo->holding_l == true && philo->holding_r == true)
			start_meal(philo, input);
	}
	return (NULL);
}

int	create_threads(t_philo **philos, t_input *input)
{
	int	i;

	input->start_time = get_time_in_ms();
	i = 0;
	while (i < input->nbr_of_philos)
	{
		if (pthread_create(&((*philos)[i].philo_thread), NULL,
			philo_routine, &((*philos)[i])))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_create(&(input->monitor_thread), NULL,
			monitor_routine, philos))
		return (EXIT_FAILURE);
	return (0);
}

int	wait_threads(t_philo **philos, t_input *input)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 0;
	while (i < input->nbr_of_philos)
	{
		if (pthread_join((*philos)[i].philo_thread, NULL) != 0)
			return_code = 1;
		i++;
	}
	if (pthread_join(input->monitor_thread, NULL) != 0)
		return_code = 1;
	return (return_code);
}
