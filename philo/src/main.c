/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:54:56 by artperez          #+#    #+#             */
/*   Updated: 2025/05/16 12:51:51 by artperez         ###   ########.fr       */
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

void	init_threads(t_philo *philos, int philo_nbr)
{
	int	i;
	
	i = 0;
	(void)philos;
	while (i < philo_nbr)
	{
		pthread_create(&philos[i].thread, NULL, exec, &philos[i]);
		i++;
	}
}

// void	exec(t_philo *philo, struct timeval *time)
// {
// 	printf("%lld %i his thinking\n", get_time(time), philo->philo_nbr);
// 	pthread_mutex_lock(&philo->left_fork->lock);
// 	printf("%lld %i has taken a fork\n", get_time(time), philo->philo_nbr);
// 	pthread_mutex_lock(&philo->right_fork->lock);
// 	printf("%lld %i has taken a fork\n", get_time(time), philo->philo_nbr);
// 	printf("%lld %i is eating\n", get_time(time), philo->philo_nbr);
// 	usleep(philo->time_to_eat * 1000);
// 	pthread_mutex_unlock(&philo->left_fork->lock);
// 	pthread_mutex_unlock(&philo->right_fork->lock);
// 	printf("%lld %i is sleeping\n", get_time(time), philo->philo_nbr);
// 	usleep(philo->time_to_sleep * 1000);
// }

void *exec(void *data)
{
	t_philo *philo;
	struct timeval	time;

	philo = (t_philo*)data;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		printf("%lld %i has taken a fork\n", get_time(&time), philo->philo_id);
		pthread_mutex_lock(&philo->right_fork->lock);
		printf("%lld %i has taken a fork\n", get_time(&time), philo->philo_id);
		printf("%lld %i is eating\n", get_time(&time), philo->philo_id);
		usleep(philo->time_to_eat * 1000);
		printf("%lld %i is thinking\n", get_time(&time), philo->philo_id);
		philo->time_to_die = 0;
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		printf("%lld %i is sleeping\n", get_time(&time), philo->philo_id);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}

long long	get_time(struct timeval *time)
{
	long long	res;

	gettimeofday(time, NULL);
	res = time->tv_sec * 1000 + time->tv_usec / 1000;
	return (res);
}

t_philo	*init_philo(char **inputs)
{
	int	philo_nbr;
	int	i;
	t_philo	*philos;
	t_fork	*forks;

	i = 0;
	philo_nbr = ft_atoi(inputs[1]);
	philos = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	forks = malloc(sizeof(t_philo) * ft_atoi(inputs[1]));
	while (i < philo_nbr)
	{
		forks[i].fork_name = i + 1;
		philos[i].philo_id = i + 1;
		philos[i].time_to_die = ft_atoi(inputs[2]);
		philos[i].time_to_eat = ft_atoi(inputs[3]);
		philos[i].time_to_sleep = ft_atoi(inputs[4]);
		if (inputs[5])
			philos[i].nbr_of_must_eat = ft_atoi(inputs[5]);
		philos[i].left_fork = &forks[i];
		if (i + 1 > philo_nbr)
			philos[i].right_fork = &forks[0];
		else
			philos[i].right_fork = &forks[i + 1];
		pthread_mutex_init(&forks[i].lock, NULL);
		pthread_mutex_init(&philos[i].lock, NULL);
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
