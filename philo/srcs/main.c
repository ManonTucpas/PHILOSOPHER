/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:51:18 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 19:23:28 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

/*
** Ici l'argument est la struct philo[i]
** A partir de la fonction begin_diner on travaille thread par thread
** On traite philo 1, puis philo 2 etc....
*/

void	*start_philo_diner(void *arg)
{
	t_philo		*a;

	a = (t_philo *)arg;
	a->left = a->id;
	a->right = (a->id + 1) % a->nb_philo;
	while (1)
	{
		pthread_mutex_lock(&(a->arg->is_die_mutex));
		if (a->arg->is_die == 1)
		{
			pthread_mutex_unlock(&(a->arg->is_die_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(a->arg->is_die_mutex));
		take_fork_and_eat(a, a->left, a->right);
		if (a->nb_philo > 1)
			let_down_forks(a, a->left, a->right);
	}
	return (NULL);
}

void	create_thread_philo(t_arg *arg)
{
	int			i;
	pthread_t	*tid;

	i = 0;
	tid = malloc(sizeof(pthread_t) * arg->nb_phi);
	if (!tid)
		return ;
	pthread_create(&arg->philo->monitor_check_die, NULL, &checker, arg->philo);
	while (i < arg->nb_phi)
	{
		pthread_create(&tid[i], NULL, &start_philo_diner, arg->philo + i);
		ft_usleep(5);
		i++;
	}
	i = 0;
	while (i < arg->nb_phi)
	{
		pthread_join(tid[i], NULL);
		pthread_join(arg->philo[i].monitor_check_die, NULL);
		i++;
	}
	free(tid);
	ft_destroy_mutex(arg);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 5 || argc == 6)
	{
		if (ft_strcmp(argv[1], "0") == 0)
			return (error("invalid argument"));
		if (check_args(argv) == 1)
			return (error("invalid argument"));
		if (init_struct_arg(&arg, argv, argc) == 1)
			return (error("invalid argument"));
		init_struct_philo(&arg);
		create_thread_philo(&arg);
	}
	else
		return (error("invalid number of arguments"));
	return (0);
}
