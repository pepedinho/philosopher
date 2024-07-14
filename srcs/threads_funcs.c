/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:29:13 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:03:36 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>
#include <stdio.h>

void	kill_all_philo(t_philo_queue *queue)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		change_status(philo, 4);
		philo = philo->next;
	}
	pthread_mutex_unlock(queue->first->print_mutex);
}

int	monitoring(t_philo_queue *queue)
{
	t_philo	*philo;
	int		max_ite;

	max_ite = queue->args->itteration;
	while (1)
	{
		philo = queue->first;
		while (philo)
		{
			if (get_status(philo) == 4)
			{
				pthread_mutex_lock(philo->print_mutex);
				printf("%lld %d died\n", get_time(philo), philo->id);
				kill_all_philo(queue);
				return (1);
			}
			else if (max_ite && queue->stop_monitoring)
				return (1);
			philo = philo->next;
		}
	}
	return (0);
}

void	thread_generation(t_philo_queue *queue)
{
	t_philo	*philo;

	philo = queue->first;
	pthread_mutex_lock(philo->print_mutex);
	while (philo)
	{
		pthread_create(philo->thread, NULL, &routine, queue);
		philo = philo->next;
	}
	pthread_mutex_unlock(queue->first->print_mutex);
	philo = queue->first;
	/*while (philo)
	{
		if (philo->status == 4)
		{
			pthread_mutex_lock(philo->print_mutex);
			printf("dead\n");
			philo = queue->first;
			while (philo)
			{
				change_status(philo, 4);
				philo = philo->next;
			}
			pthread_mutex_unlock(philo->print_mutex);
		}
		philo = philo->next;
	}*/
	monitoring(queue);
	while (philo)
	{
		pthread_join(*philo->thread, NULL);
		philo = philo->next;
	}
}
