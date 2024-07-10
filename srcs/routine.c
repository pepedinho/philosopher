/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:05:23 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:42:19 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>

t_philo	*get_by_id(t_philo_queue *queue, int *id)
{
	t_philo	*philo;

	pthread_mutex_lock(queue->mutex_g);
	philo = queue->first;
	while (philo)
	{
		pthread_mutex_lock(philo->mutex);
		if (!*id)
			*id = 1;
		if (philo->id == *id)
		{
			*id += 1;
			pthread_mutex_unlock(queue->mutex_g);
			return (pthread_mutex_unlock(philo->mutex), philo);
		}
		pthread_mutex_unlock(philo->mutex);
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
	if (!philo)
		return (printf("error %d\n", id), NULL);
	t_printf(philo, "test");
	return (NULL);
}
