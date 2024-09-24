/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 09:11:55 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/09/24 06:43:59 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
		usleep(100);
}

void	write_state(t_philo *philo, t_input *input, char *str)
{
	long	cur_time;

	cur_time = get_time_in_ms() - input->start_time;
	pthread_mutex_lock(&(input->print_lock));
	if (!stop_sim(input))
		printf("%09ld %d %s\n", cur_time, philo->id + 1, str);
	pthread_mutex_unlock(&(input->print_lock));
}

long	ft_atoi(const char *str)
{
	long	sign;
	long	result;
	long	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_if_num(int argc, char **argv)
{
	int	i;
	int	j;
	int	strl;

	i = 1;
	while (i < argc)
	{
		strl = 0;
		while (argv[i][strl] != '\0')
			strl++;
		j = 0;
		while (j < strl)
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
