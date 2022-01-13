/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer@student.42.fr <mlecuyer>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:49:29 by mlecuyer@st       #+#    #+#             */
/*   Updated: 2021/11/23 14:23:52 by mlecuyer@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_phi)
	{
		if (pthread_mutex_destroy(&arg->forks_mutex[i]))
			pthread_mutex_destroy(&arg->forks_mutex[i]);
		i++;
	}
	if (arg->forks_mutex)
		free(arg->forks_mutex);
	pthread_mutex_destroy(&arg->print_mutex);
	pthread_mutex_destroy(&arg->eat_mutex);
	pthread_mutex_destroy(&arg->is_die_mutex);
	pthread_mutex_destroy(&arg->counter_mutex);
	if (arg->philo)
		free(arg->philo);
}

int	error(char *str)
{
	printf("Error : %s\n", str);
	return (1);
}
