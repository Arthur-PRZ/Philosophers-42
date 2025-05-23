/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:54:56 by artperez          #+#    #+#             */
/*   Updated: 2025/05/23 11:14:25 by artperez         ###   ########.fr       */
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
		if (check_nbr(inputs[i]) == false)
			return (false);
		i++;
		j = 0;
	}
	return (true);
}

bool	check_nbr(char *input)
{
	char	*str;

	str = ft_itoa(ft_atoi(input));
	if (ft_strcmp(input, str) != 0)
		return (write(2, "Invalid Input : nbr must be storable in a int\n", 47),
			free(str), (false));
	free(str);
	if (ft_atoi(input) <= 0)
		return (write(2, "Invalid Input : nbr must be > 0\n", 33),
			(false));
	return (true);
}

void	*exec1(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_printf("has taken a fork\n", philo);
	while (check_end(philo) == false)
		usleep(1000);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (!check_input(argv, argc))
		return (-1);
	philos = init_philos(argv);
	init_threads(philos, ft_atoi(argv[1]));
	free_all(philos);
	return (0);
}
