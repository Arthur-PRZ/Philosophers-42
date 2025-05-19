/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:52:50 by artperez          #+#    #+#             */
/*   Updated: 2025/05/19 14:28:56 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *check_philos(void *data)
{
    t_philo *philos;
    int i;

    i = 0;
    philos = (t_philo *)data;
    while (1)
    {
        while (philos[0].philo_nbr > i)
        {
            pthread_mutex_lock(&philos[i].meal_lock);
            if (get_time() - philos[i].last_meal > philos[i].time_to_die)
            {
			    printf("\n%lld - %lli  > %i\n\n", get_time(), philos[i].last_meal, philos[i].time_to_die);
			    printf("%lld %i is died\n", get_time(), philos[i].philo_id);
                *philos[i].is_dead = true;
            }
            pthread_mutex_unlock(&philos[i].meal_lock);
            i++;
        }
        i = 0;
    }
}

void	init_threads(t_philo *philos, int philo_nbr)
{
	int	i;
	pthread_t thread;

	i = 0;
    thread = 0;
	(void)philos;
	while (i < philo_nbr)
	{
		pthread_create(&philos[i].thread, NULL, exec, &philos[i]);
		usleep(100);
		i++;
	}
	pthread_create(&thread, NULL, check_philos, philos);
	i = 0;
	while (i < philo_nbr)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(thread, NULL);
}

void *exec(void *data)
{
	t_philo *philo;

	philo = (t_philo*)data;
	philo->last_meal = get_time();
	while (philo->is_dead == false)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		printf("%lld %i has taken a fork\n", get_time(), philo->philo_id);
		pthread_mutex_lock(&philo->right_fork->lock);
		printf("%lld %i has taken a fork\n", get_time(), philo->philo_id);
		printf("%lld %i is eating\n", get_time(), philo->philo_id);
		philo->last_meal = get_time();
		usleep(philo->time_to_eat * 1000);
		printf("%lld %i is thinking\n", get_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		printf("%lld %i is sleeping\n", get_time(), philo->philo_id);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}
