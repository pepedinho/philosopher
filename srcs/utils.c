/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:27:29 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 04:15:49 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	thread_sleep(int time, t_philo *philo)
{
	unsigned long long int	start_time;

	start_time = get_time(philo);
	while (get_time(philo) - start_time < (unsigned long long)time)
	{
		if (usleep(10) != 0)
			return (0);
	}
	return (1);
}

void	fork_assign(t_philo_queue *queue, t_philo *philo, t_philo *f_fork,
		t_philo *s_fork)
{
	if (philo->id % 2 == 0)
	{
		f_fork = philo;
		if (philo->id == queue->args->nb_of_philo)
			s_fork = queue->first;
		else
			s_fork = philo->next;
	}
	else
	{
		s_fork = philo;
		if (philo->id == queue->args->nb_of_philo)
			f_fork = queue->first;
		else
			f_fork = philo->next;
	}
}

void	take_fork(t_philo_queue *queue, t_philo *philo)
{
	t_philo	*first_fork;
	t_philo	*second_fork;

	if (queue->args->nb_of_philo % 2 == 0)
	{
		if (philo->id == queue->args->nb_of_philo)
		{
			first_fork = philo;
			second_fork = queue->first;
		}
		else
		{
			first_fork = philo;
			second_fork = philo->next;
		}
	}
	else
	{
		if (philo->id == queue->args->nb_of_philo)
		{
			first_fork = queue->first;
			second_fork = philo;
		}
		else
		{
			first_fork = philo->next;
			second_fork = philo;
		}
	}
	pthread_mutex_lock(first_fork->fork_mutex);
	t_printf(philo, "has taken a fork");
	pthread_mutex_lock(second_fork->fork_mutex);
	t_printf(philo, "has taken a fork");
}

void	drop_fork(t_philo_queue *queue, t_philo *philo)
{
	t_philo	*first_fork;
	t_philo	*second_fork;

	if (queue->args->nb_of_philo % 2 == 0)
	{
		if (philo->id == queue->args->nb_of_philo)
		{
			first_fork = philo;
			second_fork = queue->first;
		}
		else
		{
			first_fork = philo;
			second_fork = philo->next;
		}
	}
	else
	{
		if (philo->id == queue->args->nb_of_philo)
		{
			first_fork = queue->first;
			second_fork = philo;
		}
		else
		{
			first_fork = philo->next;
			second_fork = philo;
		}
	}
	pthread_mutex_unlock(second_fork->fork_mutex);
	pthread_mutex_unlock(first_fork->fork_mutex);
}

int	get_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->status_mutex);
	status = philo->status;
	pthread_mutex_unlock(philo->status_mutex);
	return (status);
}

int	get_id(t_philo *philo)
{
	int	id;

	pthread_mutex_lock(philo->id_mutex);
	id = philo->id;
	pthread_mutex_unlock(philo->id_mutex);
	return (id);
}
