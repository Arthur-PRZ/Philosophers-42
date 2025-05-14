/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:54:56 by artperez          #+#    #+#             */
/*   Updated: 2025/05/14 13:31:51 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_input(char **inputs, int inputs_nbr)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (inputs_nbr < 5)
		return (write(2, "Invalid Input : Not enough args\n", 33), (false));
	else if (inputs_nbr > 6)
		return (write(2, "Invalid Input : Too many args\n", 31), (false));
	while (inputs[i])
	{
		while (inputs[i][j])
		{
			if (inputs[i][j] < '0' || inputs[i][j] > '9')
				return (write(2, "Invalid Input : Numerics char required\n",
						41), (false));
			j++;
		}
		if (ft_atoi(inputs[i]) < 0)
			return (write(2, "Invalid Input : postive nbr required\n", 38),
				(false));
		i++;
	}
	return (true);
}

void	init_mutex(t_philo	*philos, int philo_nbr)
{
	int	i;

	i = 0;
	while (i <= philo_nbr)
	{
		
	}
}

t_philo	*init_philo(char **inputs)
{
	int	philo_nbr;
	int	i;
	t_philo	*philos;
	t_fork	*forks;

	i = 1;
	philo_nbr = ft_atoi(inputs[1]);
	philos = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	forks = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	while (i < philo_nbr)
	{
		forks[i].fork_name = i;
		philos[i].time_to_die = ft_atoi(inputs[2]);
		philos[i].philo_nbr = i;
		philos[i].left_fork = forks[i];
		philos[i].right_fork = forks[i + 1];
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo *philos;

	if (!check_input(argv, argc))
		return (-1);
	philos = init_philo(argv);
	init_mutex(philos, ft_atoi(argv[1]));
	return (0);
}
