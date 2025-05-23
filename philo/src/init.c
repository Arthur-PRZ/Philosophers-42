/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:27:06 by artperez          #+#    #+#             */
/*   Updated: 2025/05/23 12:15:16 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_mutex_and_flags(t_philo *philos, t_fork *forks, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_init(&forks[i].lock, NULL);
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		pthread_mutex_init(&philos[i].meal_finish_lock, NULL);
		pthread_mutex_init(&philos[i].printf_lock, NULL);
		i++;
	}
}

static void	set_ids_bool_forks(t_philo *philos, t_fork *forks, int i, int nbr)
{
	forks[i].fork_id = i + 1;
	philos[i].philo_id = i + 1;
	philos[i].left_fork = &forks[i];
	if (nbr == 1)
		philos[i].right_fork = &forks[i];
	else if (i + 1 == nbr)
		philos[i].right_fork = &forks[0];
	else
		philos[i].right_fork = &forks[i + 1];
}

static void	init_forks_and_data(t_philo *philos, t_fork *forks,
	char **inputs, int philo_nbr)
{
	int						i;
	static int				meal_finish;
	static bool				is_dead;
	static pthread_mutex_t	is_dead_lock;

	i = -1;
	is_dead = false;
	meal_finish = 0;
	pthread_mutex_init(&is_dead_lock, NULL);
	init_mutex_and_flags(philos, forks, philo_nbr);
	while (++i < philo_nbr)
	{
		set_ids_bool_forks(philos, forks, i, philo_nbr);
		philos[i].time_to_die = ft_atoi(inputs[2]);
		philos[i].time_to_eat = ft_atoi(inputs[3]);
		philos[i].time_to_sleep = ft_atoi(inputs[4]);
		philos[i].is_dead = &is_dead;
		philos[i].is_dead_lock = &is_dead_lock;
		philos[i].philo_nbr = philo_nbr;
		if (inputs[5])
			philos[i].nbr_of_eat = ft_atoi(inputs[5]);
		else
			philos[i].nbr_of_eat = -1;
		philos[i].meal_finish = &meal_finish;
	}
}

t_philo	*init_philos(char **inputs)
{
	int		philo_nbr;
	t_philo	*philos;
	t_fork	*forks;

	philo_nbr = ft_atoi(inputs[1]);
	philos = malloc(sizeof(t_philo) * philo_nbr);
	if (!philos)
		return (NULL);
	forks = malloc(sizeof(t_fork) * philo_nbr);
	if (!forks)
	{
		free(philos);
		return (NULL);
	}
	philos[0].forks = forks;
	init_forks_and_data(philos, forks, inputs, philo_nbr);
	return (philos);
}

void	init_threads(t_philo *philos, int philo_nbr)
{
	int			i;
	pthread_t	check_thread;

	i = 0;
	if (philos[0].right_fork == NULL)
		pthread_create(&philos[0].thread, NULL, exec1, &philos[i]);
	else
	{
		while (i < philo_nbr)
		{
			philos[i].meal_eat = 0;
			philos[i].last_meal = get_time();
			pthread_create(&philos[i].thread, NULL, exec, &philos[i]);
			i++;
		}
	}
	pthread_create(&check_thread, NULL, check_philos, philos);
	pthread_join(check_thread, NULL);
	i = 0;
	while (i < philo_nbr)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
