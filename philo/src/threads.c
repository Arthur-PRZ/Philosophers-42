/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:52:50 by artperez          #+#    #+#             */
/*   Updated: 2025/05/23 12:42:52 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_philos(void *data)
{
	t_philo	*philos;
	int		i;
	int		finished_philos;

	philos = (t_philo *)data;
	while (1)
	{
		finished_philos = 0;
		i = -1;
		while (++i < philos[0].philo_nbr)
		{
			if (check_death(&philos[i]) == false)
				return (NULL);
			pthread_mutex_lock(&philos[i].meal_lock);
			if (philos[i].nbr_of_eat != -1 && philos[i].meal_eat
				== philos[i].nbr_of_eat)
				finished_philos++;
			pthread_mutex_unlock(&philos[i].meal_lock);
		}
		if (check_all_eat(&philos[0], finished_philos) == true)
			return (NULL);
		usleep(1000);
	}
}

bool	check_all_eat(t_philo *philo, int finished_philos)
{
	if (philo->nbr_of_eat != -1 && finished_philos
		== philo->philo_nbr)
	{
		printf("\n%i\n\n", finished_philos);
		pthread_mutex_lock(&philo->meal_finish_lock);
		*philo->meal_finish = philo->philo_nbr;
		pthread_mutex_unlock(&philo->meal_finish_lock);
		return (true);
	}
	return (false);
}

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->printf_lock);
		pthread_mutex_lock(philo->is_dead_lock);
		*philo->is_dead = true;
		pthread_mutex_unlock(philo->is_dead_lock);
		printf("%lld %i died\n", get_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->printf_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (true);
}

static void	fork_handler(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		ft_printf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->right_fork->lock);
		ft_printf("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->lock);
		ft_printf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->left_fork->lock);
		ft_printf("has taken a fork\n", philo);
	}
}

void	*exec(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (check_end(philo) == false && (philo->nbr_of_eat == -1
			|| philo->meal_eat < philo->nbr_of_eat))
	{
		fork_handler(philo);
		pthread_mutex_lock(&philo->meal_lock);
		ft_printf("is eating\n", philo);
		philo->last_meal = get_time();
		philo->meal_eat++;
		pthread_mutex_unlock(&philo->meal_lock);
		precise_sleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
		ft_printf("is thinking\n", philo);
		ft_printf("is sleeping\n", philo);
		precise_sleep(philo->time_to_sleep);
	}
	return (NULL);
}
