/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:08:30 by itahri            #+#    #+#             */
/*   Updated: 2024/07/13 04:51:52 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
int	thread_sleep(int time)
{
	int	i;
	int	sleep_interval;

	i = 0;
	sleep_interval = 400;
	while (i < (time * 1000 / sleep_interval))
	{
		if (usleep(sleep_interval) != 0)
			return (0);
		i++;
	}
	return (1);
}
*/

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

void	take_fork(t_philo_queue *queue, t_philo *philo)
{
	t_philo	*first_fork;
	t_philo	*second_fork;

	if (philo->id == queue->args->nb_of_philo)
	{
		first_fork = queue->first;
		second_fork = philo;
	}
	else
	{
		first_fork = philo;
		second_fork = philo->next;
	}
	pthread_mutex_lock(first_fork->fork_mutex);
	pthread_mutex_lock(second_fork->fork_mutex);
}

void	drop_fork(t_philo_queue *queue, t_philo *philo)
{
	t_philo	*first_fork;
	t_philo	*second_fork;

	if (philo->id == queue->args->nb_of_philo)
	{
		first_fork = queue->first;
		second_fork = philo;
	}
	else
	{
		first_fork = philo;
		second_fork = philo->next;
	}
	pthread_mutex_unlock(first_fork->fork_mutex);
	pthread_mutex_unlock(second_fork->fork_mutex);
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
		/*
			printf("-------------------------------------------------------------\n");
			printf("philo[%d] starting time : %lld ending_time : %lld\n",
				philo->id,
				philo->starting_time, time);
			printf("\tending_time - starting_time = %lld\n", time
				- philo->starting_time);
			printf("\t\ttime to eat : %d\n", queue->args->time_to_eat);
			printf("-------------------------------------------------------------\n");
		*/
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
	if (!check_time(philo, queue))
	{
		return (drop_fork(queue, philo), 0);
		printf("---------------debug philo [%d]--------------------\n",
			philo->id);
	}
	change_status(philo, 1);
	t_printf(philo, "has taken a fork");
	t_printf(philo, "is eating");
	change_last_eating(philo);
	thread_sleep(queue->args->time_to_eat, philo);
	if (!check_eat_time(philo, queue))
	{
		drop_fork(queue, philo);
		return (0);
	}
	drop_fork(queue, philo);
	if (philo->is_limmited_by_it)
		philo->itteration--;
	return (1);
}

int	p_sleep(t_philo_queue *queue, t_philo *philo)
{
	if (get_status(philo) == 4)
		return (0);
	change_status(philo, 2);
	t_printf(philo, "is sleeping");
	thread_sleep(queue->args->time_to_sleep, philo);
	return (1);
}

int	think(t_philo_queue *queue, t_philo *philo)
{
	if (get_status(philo) == 4)
		return (0);
	(void)queue;
	change_starting_time(philo);
	change_status(philo, 3);
	t_printf(philo, "is thinking");
	return (1);
}
