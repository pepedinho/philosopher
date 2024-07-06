/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:29:30 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:05:10 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_args
{
  int nb_of_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int itteration;
}     t_args;

typedef struct s_philo
{
  pthread_t *thread;
  pthread_mutex_t *mutex;
  int id;
  int status;
  int last_action;
  struct timeval geting_time;
  unsigned long long int starting_time;
  unsigned long long int last_eating;
  struct s_philo *next;
} t_philo;

typedef struct s_philo_queue {
  t_args *args;
  t_philo *first;
} t_philo_queue;

//args parsing
t_args	*check_args(int argc, const char **argv);
int	ft_atoi(const char *nptr);

//queue functions
t_philo_queue	*create_philo_queue(t_args *args);
void	free_queue(t_philo_queue *queue);

//time functions
unsigned long long int	get_time(t_philo *philo);
int	check_time(t_philo *philo, t_philo_queue *queue);

//routine
void*	routine(void *v_queue);

//thread functions
void	thread_generation(t_philo_queue *queue);

#endif
