/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:07:54 by itahri            #+#    #+#             */
/*   Updated: 2024/07/13 04:47:40 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>
#include <stdio.h>

/*
  status :
	1 : eat;
	2 : sleep;
	3 : think;
	4 : dead;
*/

unsigned long long int	get_time(t_philo *philo)
{
	unsigned long long int	time;

	// pthread_mutex_lock(philo->time_mutex);
	if (gettimeofday(&philo->geting_time, NULL) == -1)
		return (pthread_mutex_unlock(philo->time_mutex), 0);
	time = (philo->geting_time.tv_sec * 1000) + (philo->geting_time.tv_usec
			/ 1000);
	// pthread_mutex_unlock(philo->time_mutex);
	return (time);
}

int	check_time(t_philo *philo, t_philo_queue *queue)
{
	unsigned long long int	time;

	//	pthread_mutex_lock(queue->mutex_g);
	pthread_mutex_lock(philo->time_mutex);
	// if (philo->status == 2)
	// {
	// 	if (get_time(philo)
	// 		- philo->starting_time > (unsigned long long int)queue->args->time_to_sleep
	// 		* 1000)
	// 	{
	// 		philo->status = 4;
	// 		t_printf(philo, "is dead");
	// 		return (pthread_mutex_unlock(philo->time_mutex), 0);
	// 	}
	// }
	// else if (philo->status == 1)
	// {
	// 	if (get_time(philo)
	// 		- philo->starting_time > (unsigned long long int)queue->args->time_to_eat
	// 		* 1000)
	// 	{
	// 		philo->status = 4;
	// 		t_printf(philo, "is dead");
	// 		return (pthread_mutex_unlock(philo->time_mutex), 0);
	// 	}
	// }
	time = get_time(philo);
	dprintf(2, "TESTa : %lld\n", time - philo->last_eating);
	if (time - philo->last_eating > (unsigned long long)queue->args->time_to_die
		&& philo->last_eating)
	{
		philo->status = 4;
		t_printf(philo, "is dead");
		return (pthread_mutex_unlock(philo->time_mutex), 0);
	}
	// pthread_mutex_unlock(queue->mutex_g);
	pthread_mutex_unlock(philo->time_mutex);
	return (1);
}

int	t_printf(t_philo *philo, char *str)
{
	long long int	time;
	int				id;

	time = get_time(philo);
	if (time == 0)
		return (-1);
	pthread_mutex_lock(philo->id_mutex);
	pthread_mutex_lock(philo->print_mutex);
	id = philo->id;
	printf("%lld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->id_mutex);
	pthread_mutex_unlock(philo->print_mutex);
	return (1);
}
