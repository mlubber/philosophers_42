/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 11:38:07 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 07:08:02 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_fork(t_philo *philo, t_input *input, char l_or_r)
{
	int		*taken;
	t_fork	*fork;

	if (stop_sim(input) == false)
	{
		taken = &(philo->holding_r);
		fork = philo->r_fork;
		if (l_or_r == 'l')
		{
			taken = &(philo->holding_l);
			fork = philo->l_fork;
		}
		pthread_mutex_lock(&(fork->lock));
		if (*taken == 0 && fork->in_use == 0)
		{
			*taken = 1;
			fork->in_use = 1;
			pthread_mutex_unlock(&(fork->lock));
			write_state(philo, input, "has taken a fork");
		}
		else
			pthread_mutex_unlock(&(fork->lock));
	}
}

static void	release_fork(t_philo *philo, char l_or_r)
{
	int		*taken;
	t_fork	*fork;

	taken = NULL;
	fork = NULL;
	if (l_or_r == 'r')
	{
		taken = &(philo->holding_r);
		fork = philo->r_fork;
	}
	else if (l_or_r == 'l')
	{
		taken = &(philo->holding_l);
		fork = philo->l_fork;
	}
	pthread_mutex_lock(&(fork->lock));
	*taken = 0;
	fork->in_use = 0;
	pthread_mutex_unlock(&(fork->lock));
}

void	finished_meal(t_philo *philo, t_input *input)
{
	release_fork(philo, 'r');
	release_fork(philo, 'l');
	write_state(philo, input, "is sleeping");
	ft_usleep(input->tt_sleep);
}
