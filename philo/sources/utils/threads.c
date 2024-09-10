/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 13:24:47 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/10 14:03:21 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	create_threads(t_philo **philos, t_input *input)
{
	int	i;

	input->start_time = get_timestamp();
	i = 0;
	while (i < input->nbr_of_philos)
	{
		i++;
	}
	return (1);
}

void	philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->input->tt_eat);
	
}
