/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:59:34 by artperez          #+#    #+#             */
/*   Updated: 2025/05/23 10:59:47 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_printf(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->printf_lock);
	pthread_mutex_lock(philo->is_dead_lock);
	if (*philo->is_dead == false && (philo->nbr_of_eat == -1
			|| philo->meal_eat < philo->nbr_of_eat))
		printf("%lld %i %s", get_time(), philo->philo_id, str);
	pthread_mutex_unlock(philo->is_dead_lock);
	pthread_mutex_unlock(&philo->printf_lock);
}

void	precise_sleep(long ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
		usleep(100);
}

void	free_all(t_philo *philos)
{
	int		i;
	int		philo_nbr;
	t_fork	*forks;

	i = 0;
	if (!philos)
		return ;
	philo_nbr = philos[0].philo_nbr;
	forks = philos[0].forks;
	while (i < philo_nbr)
	{
		pthread_mutex_destroy(&philos[i].meal_lock);
		pthread_mutex_destroy(&philos[i].meal_finish_lock);
		pthread_mutex_destroy(&philos[i].printf_lock);
		pthread_mutex_destroy(&forks[i].lock);
		i++;
	}
	pthread_mutex_destroy(philos[0].is_dead_lock);
	free(forks);
	free(philos);
}
