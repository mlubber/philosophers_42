/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 08:39:09 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 07:41:18 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_input		input;
	t_philo		*philos;
	t_fork		*forks;
	int			return_code;

	return_code = 0;
	if (init_input(&input, argc, argv) == 1)
		return (EXIT_FAILURE);
	if (create_philos(&philos, &forks, &input) == 1)
		return (EXIT_FAILURE);
	if (create_threads(&philos, &input) == 1)
		return_code = stop_threads(&input);
	if (wait_threads(&philos, &input) == 1)
	{
		free(philos);
		free(forks);
		return (EXIT_FAILURE);
	}
	free(philos);
	free(forks);
	return (return_code);
}
