/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 11:17:33 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/10 14:38:14 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	init_philo(t_philo *philo, t_fork **forks, t_input *input, int id)
{
	philo->input = input;
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->l_taken = 0;
	philo->r_taken = 0;
	philo->r_fork = &((*forks)[id]);
	if (id == (input->nbr_of_philos - 1))
		philo->l_fork = &((*forks)[0]);
	else
		philo->l_fork = &((*forks)[id + 1]);
	philo->l_fork->used = 0;
	pthread_mutex_init(&(philo->last_meal_mutex), NULL);
	pthread_mutex_init(&(philo->l_fork->lock_mutex), NULL);
}

int	create_philos(t_philo **philos, t_fork **forks, t_input *input)
{
	int	i;

	*philos = malloc(input->nbr_of_philos * sizeof(t_philo));
	if (*philos == NULL)
		return (0);
	*forks = malloc(input->nbr_of_philos * sizeof(t_fork));
	if (*forks == NULL)
	{
		free(*philos);
		return (0);
	}
	i = 0;
	while (i < input->nbr_of_philos)
	{
		init_philo(&((*philos)[i]), forks, input, i);
		i++;
	}
	return (1);
}

int	init_input(t_input *input, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong input\n");
		return (0);
	}
	else if (check_if_num(argc, argv) == 1)
	{
		printf("numeric values required\n");
		return (0);
	}
	input->nbr_of_philos = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->max_meals = ft_atoi(argv[5]);
	else
		input->max_meals = -1;
	input->is_dead = 0;
	if (input->nbr_of_philos <= 0 || input->tt_die < 0
		|| input->tt_eat < 0 || input->tt_sleep < 0)
		return (0);
	pthread_mutex_init(&(input->print_mutex), NULL);
	pthread_mutex_init(&(input->is_dead_mutex), NULL);
	return (1);
}
