/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 11:17:33 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 08:50:26 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

static int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong input\n");
		return (EXIT_FAILURE);
	}
	else if (check_if_num(argc, argv) == 1)
	{
		printf("numeric values required\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	init_input(t_input *input, int argc, char **argv)
{
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	input->nbr_of_philos = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->max_meals = ft_atoi(argv[5]);
	else
		input->max_meals = -1;
	if (input->nbr_of_philos <= 0 || input->tt_die < 0 || input->tt_eat < 0
		|| input->tt_sleep < 0)
		return (EXIT_FAILURE);
	input->sim_stop = 0;
	pthread_mutex_init(&(input->print_lock), NULL);
	pthread_mutex_init(&(input->sim_stop_lock), NULL);
	pthread_mutex_init(&(input->eat_lock), NULL);
	return (0);
}

void	init_philo(t_philo *philo, t_fork **forks, t_input *input, int i)
{
	philo->input = input;
	philo->id = i;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->holding_r = 0;
	philo->holding_l = 0;
	philo->r_fork = &((*forks)[i]);
	if (i == input->nbr_of_philos - 1)
		philo->l_fork = &((*forks)[0]);
	else
		philo->l_fork = &((*forks)[i + 1]);
	philo->l_fork->in_use = 0;
	pthread_mutex_init(&(philo->l_fork->lock), NULL);
	pthread_mutex_init(&(philo->last_meal_lock), NULL);
}

int	create_philos(t_philo **philos, t_fork **forks, t_input *input)
{
	int	i;

	*philos = malloc(input->nbr_of_philos * sizeof(t_philo));
	if ((*philos) == NULL)
		return (EXIT_FAILURE);
	*forks = malloc(input->nbr_of_philos * sizeof(t_fork));
	if ((*forks) == NULL)
	{
		free(*philos);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < input->nbr_of_philos)
	{
		init_philo(&(*philos)[i], forks, input, i);
		i++;
	}
	return (0);
}
