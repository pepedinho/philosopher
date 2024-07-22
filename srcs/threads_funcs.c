/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:29:13 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 04:27:34 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>

void	kill_all_philo(t_philo_queue *queue)
{
	t_philo					*philo;
	unsigned long long int	time;

	philo = queue->first;
	pthread_mutex_lock(philo->print_mutex);
	time = get_time(philo);
	printf("%lld %d died\n", time, philo->id);
	while (philo)
	{
		change_status(philo, 4);
		philo = philo->next;
	}
	pthread_mutex_unlock(queue->first->print_mutex);
}

int	has_to_stop(t_philo_queue *queue)
{
	pthread_mutex_lock(queue->mutex_g);
	if (queue->stop_monitoring)
		return (pthread_mutex_unlock(queue->mutex_g), 1);
	pthread_mutex_unlock(queue->mutex_g);
	return (0);
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
			if (!check_time(philo, queue))
				return (kill_all_philo(queue), 1);
			if (get_status(philo) == 4)
				return (kill_all_philo(queue), 1);
			else if (max_ite && has_to_stop(queue))
				return (1);
			philo = philo->next;
			usleep(5);
		}
	}
	return (0);
}

void	thread_generation(t_philo_queue *queue)
{
	t_philo	*philo;

	philo = queue->first;
	if (queue->args->nb_of_philo == 1)
	{
		printf("%lld %d is thinking\n", get_time(philo), philo->id);
		printf("%lld %d is died\n", get_time(philo), philo->id);
		return ;
	}
	pthread_mutex_lock(philo->print_mutex);
	while (philo)
	{
		pthread_create(philo->thread, NULL, &routine, queue);
		philo = philo->next;
	}
	pthread_mutex_unlock(queue->first->print_mutex);
	philo = queue->first;
	monitoring(queue);
	while (philo)
	{
		pthread_join(*philo->thread, NULL);
		philo = philo->next;
	}
}
