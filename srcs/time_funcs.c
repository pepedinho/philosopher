/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:07:54 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 21:14:20 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
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

	if (gettimeofday(&philo->geting_time, NULL) == -1)
		return (0);
	time = (philo->geting_time.tv_sec * 1000) + (philo->geting_time.tv_usec
			/ 1000);
	return (time);
}

int	check_time(t_philo *philo, t_philo_queue *queue)
{
	if (philo->status == 2)
	{
		if (get_time(philo)
			- philo->starting_time > (unsigned long long int)queue->args->time_to_sleep
			* 1000)
		{
			philo->status = 4;
			return (printf("death time : %lld\n", get_time(philo)), 0);
		}
	}
	else if (philo->status == 1)
	{
		if (get_time(philo)
			- philo->starting_time > (unsigned long long int)queue->args->time_to_eat
			* 1000)
		{
			philo->status = 4;
			return (printf("death time : %lld\n", get_time(philo)), 0);
		}
	}
	if (get_time(philo)
		- philo->last_eating > (unsigned long long)queue->args->time_to_die)
	{
		philo->status = 4;
		return (printf("death time : %lld\n", get_time(philo)), 0);
	}
	return (1);
}
