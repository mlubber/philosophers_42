/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 08:39:09 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/10 14:48:03 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_input		input;
	t_philo		*philos;
	t_fork		*forks;

	if (init_input(&input, argc, argv) == 0)
		return (1);
	if (create_philos(&philos, &forks, &input) == 0)
		return (1);
	printf("Number of Philosophers: %d\n", input.nbr_of_philos);
	printf("Time to die: %lu\n", input.tt_die);
	printf("Time to eat: %lu\n", input.tt_eat);
	printf("Time to sleep: %lu\n", input.tt_sleep);
	if (argc == 6)
		printf("Number of meals: %d\n", input.max_meals);
	return (0);
}
