/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:56 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 18:57:27 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_nb_eat(t_philo *a)
{
	if (a->arg->nb_tot_meal > 0)
	{
		pthread_mutex_lock(&(a->arg->counter_mutex));
		if (a->arg->global_counter_eat == a->arg->nb_phi)
		{
			pthread_mutex_unlock(&(a->arg->counter_mutex));
			pthread_mutex_lock(&a->arg->is_die_mutex);
			a->arg->is_die = 1;
			pthread_mutex_unlock(&a->arg->is_die_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&(a->arg->counter_mutex));
	}
	return (0);
}

void	*checker(void *arg)
{
	t_philo	*a;

	a = (t_philo *)arg;
	while (1)
	{
		if (check_nb_eat(a) == -1)
			return (NULL);
		pthread_mutex_lock(&(a->arg->eat_mutex));
		if (current_time() > a->t_lst_eat + a->arg->t_to_die)
		{
			pthread_mutex_unlock(&(a->arg->eat_mutex));
			write_philo_status("died", a);
			pthread_mutex_lock(&a->arg->is_die_mutex);
			a->arg->is_die = 1;
			pthread_mutex_unlock(&a->arg->is_die_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&(a->arg->eat_mutex));
		ft_usleep(5);
	}
	return (NULL);
}
