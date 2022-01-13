/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer@student.42.fr <mlecuyer>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:51:38 by mlecuyer          #+#    #+#             */
/*   Updated: 2021/11/24 15:04:38 by mlecuyer@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_arg;

typedef struct s_philo
{
	int						id;
	int						nb_philo;
	int						left;
	int						nb_eat;
	int						right;
	pthread_t				monitor_check_die;
	struct s_arg			*arg;
	unsigned int			t_lst_eat;
	unsigned int			time_of_die;
}				t_philo;

typedef struct s_arg
{
	int					is_die;
	int					nb_phi;
	int					t_to_die;
	int					t_to_sleep;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		phi_alone;
	pthread_mutex_t		is_die_mutex;
	pthread_mutex_t		counter_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		*forks_mutex;
	int					t_to_eat;
	unsigned int		t_start;
	t_philo				*philo;
	int					global_counter_eat;
	int					nb_tot_meal;
}					t_arg;

/* 
** TOOLS
*/
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				error(char *str);
int				check_args(char **av);
unsigned int	current_time(void);
void			ft_usleep(unsigned int ms_time);
int				ft_strcmp(char *s1, char *s2);

/*
** INITS
*/
int				init_struct_arg(t_arg *arg, char **argv, int argc);
void			init_struct_philo(t_arg *arg);

/*
** CORE FUNCTIONS
*/
void			take_fork_and_eat(t_philo *a, int left, int right);
void			let_down_forks(t_philo *p, int left, int right);
void			write_philo_status(char *str, t_philo *p);
void			*checker(void *arg);
void			ft_destroy_mutex(t_arg *arg);
void			*checker_eat(void *arg);
void			*checker_eat(void *arg);

#endif