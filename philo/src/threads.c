/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:52:50 by artperez          #+#    #+#             */
/*   Updated: 2025/05/21 14:38:53 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *check_philos(void *data)
{
    t_philo *philos;
    int i;
    int finished_philos;

    i = 0;
    philos = (t_philo *)data;
    while (1)
    {
        finished_philos = 0;
        i = 0;
        while (i < philos[0].philo_nbr)
        {
            pthread_mutex_lock(&philos[i].meal_lock);
            if (get_time() - philos[i].last_meal > philos[i].time_to_die)
            {
                pthread_mutex_lock(&philos[i].printf_lock);
				pthread_mutex_lock(philos[i].is_dead_lock);
                *philos[i].is_dead = true;
				pthread_mutex_unlock(philos[i].is_dead_lock);
                printf("%lld %i died\n", get_time(), philos[i].philo_id);
                pthread_mutex_unlock(&philos[i].printf_lock);
                pthread_mutex_unlock(&philos[i].meal_lock);
                return (NULL);
            }
            if (philos[i].nbr_of_eat != -1 && philos[i].meal_eat >= philos[i].nbr_of_eat)
                finished_philos++;
            pthread_mutex_unlock(&philos[i].meal_lock);
            i++;
        }
        if (philos[0].nbr_of_eat != -1 && finished_philos == philos[0].philo_nbr)
        {
            pthread_mutex_lock(&philos[0].meal_finish_lock);
            *philos[0].meal_finish = philos[0].philo_nbr;
            pthread_mutex_unlock(&philos[0].meal_finish_lock);
            return (NULL);
        }
        usleep(1000);
    }
}

void	init_threads(t_philo *philos, int philo_nbr)
{
	int	i;
	pthread_t check_thread;

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

void	ft_printf(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->printf_lock);
	pthread_mutex_lock(philo->is_dead_lock);
	if (*philo->is_dead == false && (philo->nbr_of_eat == -1 || philo->meal_eat < philo->nbr_of_eat))
		printf("%lld %i %s", get_time(), philo->philo_id, str);
	pthread_mutex_unlock(philo->is_dead_lock);
	pthread_mutex_unlock(&philo->printf_lock);
}

void *exec1(void *data)
{
	t_philo *philo;

	philo = (t_philo*)data;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_printf("has taken a fork\n", philo);
	while (check_end(philo) == false)
		usleep(1000);
	return (NULL);
}

bool	check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->is_dead_lock);
	if(*philo->is_dead == false)
	{
		pthread_mutex_unlock(philo->is_dead_lock);
		return (false);
	}	
	pthread_mutex_unlock(philo->is_dead_lock);
	return (true);
}

void *exec(void *data)
{
	t_philo *philo;
	pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

	philo = (t_philo*)data;
	if (philo->left_fork->fork_name < philo->right_fork->fork_name)
	{
		first_fork = &philo->left_fork->lock;
		second_fork = &philo->right_fork->lock;
	}
	else
	{
		first_fork = &philo->right_fork->lock;
		second_fork = &philo->left_fork->lock;
	}
	if (philo->philo_id % 2 == 0)
		usleep(5000);
	while (check_end(philo) == false && (philo->nbr_of_eat == -1 || philo->meal_eat < philo->nbr_of_eat))
	{
		pthread_mutex_lock(first_fork);
		ft_printf("has taken a fork\n", philo);
		pthread_mutex_lock(second_fork);
		ft_printf("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->meal_lock);
		ft_printf("is eating\n", philo);
		philo->last_meal = get_time();
		philo->meal_eat++;
		pthread_mutex_unlock(&philo->meal_lock);
		usleep(philo->time_to_eat * 1000);
		ft_printf("is thinking\n", philo);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		ft_printf("is sleeping\n", philo);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}
