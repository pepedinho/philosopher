/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:05:23 by itahri            #+#    #+#             */
/*   Updated: 2024/07/13 04:45:41 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>
#include <unistd.h>

t_philo	*get_by_id(t_philo_queue *queue, int *id)
{
	t_philo	*philo;

	pthread_mutex_lock(queue->mutex_g);
	philo = queue->first;
	while (philo && *id <= queue->args->nb_of_philo)
	{
		pthread_mutex_lock(philo->id_mutex);
		if (!*id)
			*id = 1;
		if (philo->id == *id)
		{
			*id += 1;
			pthread_mutex_unlock(philo->id_mutex);
			pthread_mutex_unlock(queue->mutex_g);
			return (philo);
		}
		pthread_mutex_unlock(philo->id_mutex);
		philo = philo->next;
	}
	pthread_mutex_unlock(queue->mutex_g);
	return (NULL);
}

void	*routine(void *v_queue)
{
	t_philo_queue	*queue;
	t_philo			*philo;
	static int		id;
	int				i;
	int				max_ite;

	queue = v_queue;
	philo = get_by_id(queue, &id);
	max_ite = 0;
	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_unlock(philo->print_mutex);
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(queue->mutex_g);
	max_ite = queue->args->itteration;
	pthread_mutex_unlock(queue->mutex_g);
	i = 0;
	if (philo->is_limmited_by_it)
	{
		while (philo->itteration)
		{
			if (!think(queue, philo))
				break ;
			if (!eat(queue, philo))
				break ;
			if (!p_sleep(queue, philo))
				break ;
			if (!check_time(philo, queue))
				break ;
			i++;
		}
	}
	else
	{
		while (1)
		{
			if (!think(queue, philo))
				break ;
			if (!eat(queue, philo))
				break ;
			if (!p_sleep(queue, philo))
				break ;
			if (!check_time(philo, queue))
				break ;
		}
		// t_printf(philo, "dead debug");
	}
	if (max_ite)
	{
		pthread_mutex_lock(queue->mutex_g);
		queue->stop_monitoring = 1;
		pthread_mutex_unlock(queue->mutex_g);
	}
	return (NULL);
}
