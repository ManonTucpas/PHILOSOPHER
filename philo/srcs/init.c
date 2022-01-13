/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:15:46 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 18:11:17 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_arg *arg)
{
	int	i;

	i = 0;
	arg->forks_mutex = malloc(sizeof(pthread_mutex_t) * arg->nb_phi);
	if (!arg->forks_mutex)
		return (1);
	while (i < arg->nb_phi)
	{
		pthread_mutex_init(&(arg->forks_mutex[i]), NULL);
		i++;
	}
	pthread_mutex_init((&(arg->print_mutex)), NULL);
	pthread_mutex_init((&(arg->phi_alone)), NULL);
	pthread_mutex_init((&(arg->eat_mutex)), NULL);
	pthread_mutex_init((&(arg->is_die_mutex)), NULL);
	pthread_mutex_init((&(arg->counter_mutex)), NULL);
	return (0);
}

void	init_struct_philo(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * arg->nb_phi);
	if (!philo)
		return ;
	i = 0;
	while (i < arg->nb_phi)
	{
		philo[i].id = i;
		philo[i].nb_philo = arg->nb_phi;
		philo[i].nb_eat = 0;
		philo[i].t_lst_eat = arg->t_start;
		philo[i].arg = arg;
		i++;
	}
	arg->philo = philo;
}

int	init_struct_arg(t_arg *arg, char **argv, int argc)
{
	arg->t_start = current_time();
	arg->nb_phi = ft_atoi(argv[1]);
	arg->t_to_die = ft_atoi(argv[2]);
	arg->t_to_eat = ft_atoi(argv[3]);
	arg->t_to_sleep = ft_atoi(argv[4]);
	arg->global_counter_eat = 0;
	arg->is_die = 0;
	if (argc == 6)
		arg->nb_tot_meal = ft_atoi(argv[5]);
	else
		arg->nb_tot_meal = -1;
	if (arg->t_to_die == 0 || arg->t_to_eat == 0 || arg->t_to_sleep == 0
		|| arg->nb_tot_meal == 0 || arg->nb_phi > 200)
		return (1);
	if (init_mutex(arg) == 1)
	{
		ft_destroy_mutex(arg);
		return (1);
	}
	return (0);
}
