/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:05:23 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 04:17:52 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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

void	ite_loop(t_philo_queue *queue, t_philo *philo)
{
	while (philo->itteration)
	{
		if (!think(queue, philo))
			break ;
		if (!eat(queue, philo))
			break ;
		if (!p_sleep(queue, philo))
			break ;
	}
}

void	classic_loop(t_philo_queue *queue, t_philo *philo)
{
	while (1)
	{
		if (!think(queue, philo))
			break ;
		if (!eat(queue, philo))
			break ;
		if (!p_sleep(queue, philo))
			break ;
	}
}

void	*routine(void *v_queue)
{
	t_philo_queue	*queue;
	t_philo			*philo;
	static int		id;
	int				max_ite;

	queue = v_queue;
	philo = get_by_id(queue, &id);
	max_ite = 0;
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(queue->mutex_g);
	max_ite = queue->args->itteration;
	pthread_mutex_unlock(queue->mutex_g);
	if (philo->is_limmited_by_it)
		ite_loop(queue, philo);
	else
		classic_loop(queue, philo);
	if (max_ite)
	{
		pthread_mutex_lock(queue->mutex_g);
		queue->stop_monitoring = 1;
		pthread_mutex_unlock(queue->mutex_g);
	}
	return (NULL);
}
