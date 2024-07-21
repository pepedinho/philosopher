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

	if (gettimeofday(&philo->geting_time, NULL) == -1)
		return (pthread_mutex_unlock(philo->time_mutex), 0);
	time = (philo->geting_time.tv_sec * 1000) + (philo->geting_time.tv_usec
			/ 1000);
	return (time);
}

int	check_time(t_philo *philo, t_philo_queue *queue)
{
	unsigned long long int	time;

	pthread_mutex_lock(philo->time_mutex);
	time = get_time(philo);
	// if (philo->last_eating)
	//	dprintf(2, "TESTa : %lld\n", time - philo->last_eating);
	if (philo->last_eating != 0 && time
		- philo->last_eating > (unsigned long long)queue->args->time_to_die)
	{
		change_status(philo, 4);
		return (pthread_mutex_unlock(philo->time_mutex), 0);
	}
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
	if (get_status(philo) == 4)
	{
		pthread_mutex_unlock(philo->id_mutex);
		return (pthread_mutex_unlock(philo->print_mutex), -1);
	}
	id = philo->id;
	printf("%lld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->id_mutex);
	pthread_mutex_unlock(philo->print_mutex);
	return (1);
}
