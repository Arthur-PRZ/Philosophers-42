/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artperez <artperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:24:39 by artperez          #+#    #+#             */
/*   Updated: 2025/05/14 12:17:58 by artperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static size_t	ft_intlen(int n)
{
	size_t	intlen;

	intlen = 0;
	if (n <= 0)
	{
		if (n == -2147483648)
		{
			return (11);
		}
		n *= -1;
		intlen++;
	}
	while (n >= 1)
	{
		n /= 10;
		intlen++;
	}
	return (intlen);
}

static char	*gogotransfo(char *str, long n, size_t len)
{
	int	negative;

	negative = 0;
	if (n < 0)
	{
		n *= -1;
		negative++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (len - 1 > 0)
	{
		str[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	if (negative == 1)
		str[0] = '-';
	else
		str[0] = (n % 10) + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	str = NULL;
	len = ft_intlen(n);
	str = gogotransfo(str, (long)n, len);
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	signe;

	a = 0;
	i = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			signe *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		a = a * 10 + (str[i] - 48);
		i++;
	}
	return (a * signe);
}
