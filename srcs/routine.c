/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:05:23 by itahri            #+#    #+#             */
/*   Updated: 2024/07/11 01:09:15 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>

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

	queue = v_queue;
	philo = get_by_id(queue, &id);
	pthread_mutex_lock(philo->mutex);
	t_printf(philo, "test");
	pthread_mutex_unlock(philo->mutex);
	if (philo->id % 2)
		eat(queue, philo);
	return (NULL);
}
