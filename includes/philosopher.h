/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:29:30 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 19:38:17 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

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
  t_args *args;
  pthread_t *thread;
  int id;
  struct s_philo *next;
} t_philo;

typedef struct s_philo_queue {
  t_philo *first;
} t_philo_queue;

//args parsing
t_args	*check_args(int argc, const char **argv);
int	ft_atoi(const char *nptr);

//queue functions
t_philo_queue	*create_philo_queue(t_args *args);
void	free_queue(t_philo_queue *queue);

#endif
