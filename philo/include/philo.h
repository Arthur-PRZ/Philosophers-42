/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:55:46 by artperez          #+#    #+#             */
/*   Updated: 2025/05/15 13:05:53 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_fork
{
    int fork_name;
	pthread_mutex_t lock;
}   t_fork;

typedef enum s_do 
{
    HAS_EAT,
    HAS_SLEEP,
} t_do;

typedef struct s_philo
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_of_must_eat;
    int philo_nbr;
	pthread_t *thread;
    t_do    has;
	pthread_mutex_t lock;
    struct s_fork   *right_fork;
    struct s_fork   *left_fork;
}   t_philo;

// static size_t	ft_intlen(int n);
bool	check_input(char **inputs, int inputs_nbr);
// static char	*gogotransfo(char *str, long n, size_t len);
char	*ft_itoa(int n);
int	ft_atoi(const char *str);
void	init_threads(t_philo *philos, int philo_nbr);
long long	get_time(struct timeval *time);
void	*exec(void *data);

#endif
