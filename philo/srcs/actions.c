/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:43:14 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 19:23:16 by mlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	write_philo_status(char *str, t_philo *p)
{
	if (ft_strcmp("died", str) == 0)
	{
		pthread_mutex_lock(&p->arg->is_die_mutex);
		p->arg->is_die = 1;
		pthread_mutex_unlock(&p->arg->is_die_mutex);
		pthread_mutex_lock(&p->arg->print_mutex);
		printf("%u %d %s\n", current_time()
			- p->arg->t_start, p->id + 1, str);
		pthread_mutex_unlock(&p->arg->print_mutex);
		return ;
	}
	pthread_mutex_lock(&p->arg->is_die_mutex);
	if (p->arg->is_die == 0)
	{
		pthread_mutex_unlock(&p->arg->is_die_mutex);
		pthread_mutex_lock(&p->arg->print_mutex);
		printf("%u %d %s\n", current_time()
			- p->arg->t_start, p->id + 1, str);
		pthread_mutex_unlock(&p->arg->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&p->arg->is_die_mutex);
}

static int	check_phi_alone_actions(t_philo *p, int left)
{
	if (p->arg->nb_phi == 1)
	{
		pthread_mutex_lock(&(p->arg->forks_mutex[left]));
		write_philo_status("has taken a fork", p);
		pthread_mutex_unlock(&(p->arg->forks_mutex[left]));
		while (1)
		{
			pthread_mutex_lock(&p->arg->is_die_mutex);
			if (p->arg->is_die == 1)
			{
				pthread_mutex_unlock(&p->arg->is_die_mutex);
				return (1);
			}
			pthread_mutex_unlock(&p->arg->is_die_mutex);
		}
		return (0);
	}
	return (0);
}

void	take_fork_and_eat(t_philo *p, int left, int right)
{
	if (check_phi_alone_actions(p, left) == 1)
		return ;
	pthread_mutex_lock(&(p->arg->forks_mutex[left]));
	write_philo_status("has taken a fork", p);
	pthread_mutex_lock(&(p->arg->forks_mutex[right]));
	write_philo_status("has taken a fork", p);
	write_philo_status("is eating", p);
	pthread_mutex_lock(&(p->arg->eat_mutex));
	p->t_lst_eat = current_time();
	pthread_mutex_unlock(&(p->arg->eat_mutex));
	p->nb_eat++;
	if (p->nb_eat == p->arg->nb_tot_meal)
	{
		pthread_mutex_lock(&(p->arg->counter_mutex));
		p->arg->global_counter_eat++;
		pthread_mutex_unlock(&(p->arg->counter_mutex));
	}
	ft_usleep(p->arg->t_to_eat);
}

void	let_down_forks(t_philo *p, int left, int right)
{
	write_philo_status("is sleeping", p);
	pthread_mutex_unlock(&(p->arg->forks_mutex[right]));
	pthread_mutex_unlock(&(p->arg->forks_mutex[left]));
	ft_usleep(p->arg->t_to_sleep);
	write_philo_status("is thinking", p);
}
