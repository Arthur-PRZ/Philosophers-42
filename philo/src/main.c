/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:54:56 by artperez          #+#    #+#             */
/*   Updated: 2025/05/19 14:29:13 by artperez         ###   ########.fr       */
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
		j = 0;
	}
	return (true);
}

long long	get_time(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


t_philo	*init_philo(char **inputs)
{
	int	philo_nbr;
	int	i;
	bool	is_dead;
	t_philo	*philos;
	t_fork	*forks;

	i = 0;
	philo_nbr = ft_atoi(inputs[1]);
	philos = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	forks = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	is_dead = false;
	while (i < philo_nbr)
	{
		forks[i].fork_name = i + 1;
		philos[i].philo_id = i + 1;
		philos[i].time_to_die = ft_atoi(inputs[2]);
		philos[i].time_to_eat = ft_atoi(inputs[3]);
		philos[i].time_to_sleep = ft_atoi(inputs[4]);
		philos[i].is_dead = false;
		philos[i].philo_nbr = philo_nbr;
		if (inputs[5])
			philos[i].nbr_of_must_eat = ft_atoi(inputs[5]);
		philos[i].left_fork = &forks[i];
		if (i + 1 == philo_nbr)
			philos[i].right_fork = &forks[0];
		else
			philos[i].right_fork = &forks[i + 1];
		pthread_mutex_init(&forks[i].lock, NULL);
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo *philos;

	if (!check_input(argv, argc))
		return (-1);
	philos = init_philo(argv);
	init_threads(philos, ft_atoi(argv[1]));
	return (0);
}
