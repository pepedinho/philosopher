/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:08:30 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 04:22:45 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	change_status(t_philo *philo, int new_status)
{
	pthread_mutex_lock(philo->status_mutex);
	philo->status = new_status;
	pthread_mutex_unlock(philo->status_mutex);
}

void	change_starting_time(t_philo *philo)
{
	pthread_mutex_lock(philo->time_mutex);
	philo->starting_time = get_time(philo);
	pthread_mutex_unlock(philo->time_mutex);
}

void	change_last_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->time_mutex);
	philo->last_eating = get_time(philo);
	pthread_mutex_unlock(philo->time_mutex);
}

int	check_eat_time(t_philo *philo, t_philo_queue *queue)
{
	unsigned long long int	time;

	pthread_mutex_lock(philo->time_mutex);
	time = get_time(philo);
	if (time
		- philo->last_eating > (long long unsigned)queue->args->time_to_eat)
	{
		pthread_mutex_unlock(philo->time_mutex);
		change_status(philo, 4);
		return (0);
	}
	pthread_mutex_unlock(philo->time_mutex);
	return (1);
}

int	eat(t_philo_queue *queue, t_philo *philo)
{
	if (get_status(philo) == 4)
		return (0);
	take_fork(queue, philo);
	if (get_status(philo) == 4)
		return (drop_fork(queue, philo), 0);
	change_status(philo, 1);
	t_printf(philo, "is eating");
	change_last_eating(philo);
	thread_sleep(queue->args->time_to_eat, philo);
	/*if (!check_eat_time(philo, queue))
	{
		drop_fork(queue, philo);
		return (0);
	}*/
	drop_fork(queue, philo);
	if (philo->is_limmited_by_it)
		philo->itteration--;
	return (1);
}
