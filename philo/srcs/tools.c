/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:40:15 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 18:11:36 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	i = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -129)
			return (1);
		i++;
	}
	return (0);
}

unsigned int	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	ft_usleep(unsigned int ms_time)
{
	unsigned int	start;

	start = 0;
	start = current_time();
	while ((current_time() - start) < ms_time)
		usleep(ms_time / 10);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (!s1[i] || !s2[i])
			return (1);
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
