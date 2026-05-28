/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:55:46 by artperez          #+#    #+#             */
/*   Updated: 2025/05/23 12:14:57 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h> 

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philo
{
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	meal_finish_lock;
	pthread_mutex_t	*is_dead_lock;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
	int				*meal_finish;
	int				philo_id;
	int				meal_eat;
	long long		last_meal;
	int				philo_nbr;
	bool			*is_dead;
	pthread_t		thread;
	struct s_fork	*forks;
	struct s_fork	*right_fork;
	struct s_fork	*left_fork;
}	t_philo;

void		free_all(t_philo *philos);
bool		check_death(t_philo *philo);
bool		check_nbr(char *input);
void		precise_sleep(long ms);
t_philo		*init_philos(char **inputs);
bool		check_input(char **inputs, int inputs_nbr);
bool		check_end(t_philo *philo);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
void		init_threads(t_philo *philos, int philo_nbr);
long long	get_time(void);
void		*exec(void *data);
void		ft_printf(char *str, t_philo *philo);
void		*exec1(void *data);
int			ft_strcmp(char *s1, char *s2);
bool		check_all_eat(t_philo *philo, int finished_philos);
void		*check_philos(void *data);

#endif
