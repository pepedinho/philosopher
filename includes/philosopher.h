/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:29:30 by itahri            #+#    #+#             */
/*   Updated: 2024/07/11 00:57:07 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <bits/types/struct_timeval.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int						nb_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						itteration;
}							t_args;

typedef struct s_philo
{
	pthread_t				*thread;
	pthread_mutex_t			*mutex;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			*fork_mutex;
	pthread_mutex_t			*id_mutex;
	pthread_mutex_t			*status_mutex;
	pthread_mutex_t			*time_mutex;
	int						is_limmited_by_it;
	int						itteration;
	int						id;
	int						status;
	int						last_action;
	struct timeval			geting_time;
	unsigned long long int	starting_time;
	unsigned long long int	last_eating;
	struct s_philo			*next;
}							t_philo;

typedef struct s_philo_queue
{
	t_args					*args;
	pthread_mutex_t			*mutex_g;
	t_philo					*first;
	int						stop_monitoring;
}							t_philo_queue;

// args parsing
t_args						*check_args(int argc, const char **argv);
int							ft_atoi(const char *nptr);

// queue functions
t_philo_queue				*create_philo_queue(t_args *args);
void						free_queue(t_philo_queue *queue);

// time functions
unsigned long long int		get_time(t_philo *philo);
int							check_time(t_philo *philo, t_philo_queue *queue);
int							t_printf(t_philo *philo, char *str);

// routine
void						*routine(void *v_queue);

// thread functions
void						thread_generation(t_philo_queue *queue);

// actions
int							eat(t_philo_queue *queue, t_philo *philo);
int							think(t_philo_queue *queue, t_philo *philo);
int							p_sleep(t_philo_queue *queue, t_philo *philo);
int							get_id(t_philo *philo);
void						change_status(t_philo *philo, int new_status);
int							get_status(t_philo *philo);

#endif
