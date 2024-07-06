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

void	thread_generation(t_philo_queue *queue)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		pthread_create(philo->thread, NULL, &routine, queue);
		philo = philo->next;
	}
	philo = queue->first;
	while (philo)
	{
		pthread_join(*philo->thread, NULL);
		philo = philo->next;
	}
}
