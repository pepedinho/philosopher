/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:05:23 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:42:19 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>

/*
  status :
	1 : eat;
	2 : sleep;
	3 : think;
	4 : dead;
*/

int	is_eating(t_philo_queue *queue, int id)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		if (philo->id == id)
		{
			if (philo->status == 1)
				return (1);
			return (0);
		}
		philo = philo->next;
	}
	return (0);
}

int	fork_available(t_philo_queue *queue, t_philo *philo)
{
	if (philo->id > 0 && philo->id < queue->args->nb_of_philo)
	{
		if (is_eating(queue, philo->id + 1) || is_eating(queue, philo->id - 1))
			return (0);
	}
	else
	{
		if (philo->id == 0)
		{
			if (is_eating(queue, philo->id + 1) || is_eating(queue,
					queue->args->nb_of_philo))
				return (0);
		}
		else if (philo->id == queue->args->nb_of_philo)
		{
			if (is_eating(queue, 0) || is_eating(queue, philo->id - 1))
				return (0);
		}
	}
	return (1);
}

void	eat(t_philo_queue *queue, t_philo *philo)
{
	philo->starting_time = get_time(philo);
	philo->last_eating = get_time(philo);
	philo->status = 1;
	usleep(queue->args->time_to_eat * 1000);
	printf("%lld %d is eating\n", philo->starting_time, philo->id);
}

void	p_sleep(t_philo_queue *queue, t_philo *philo)
{
	philo->starting_time = get_time(philo);
	philo->status = 2;
	usleep(queue->args->time_to_sleep * 1000);
	printf("%lld %d is sleeping\n", philo->starting_time, philo->id);
}

void	think(t_philo_queue *queue, t_philo *philo)
{
	int	i;

	i = 0;
	philo->starting_time = get_time(philo);
	philo->status = 3;
	if (philo->id > 0 && philo->id < queue->args->nb_of_philo)
	{
		while (!fork_available(queue, philo))
			i++;
	}
	else if (philo)
		printf("%lld %d is thinking\n", philo->starting_time, philo->id);
}

int	is_sleeping(t_philo_queue *queue, int id)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		if (philo->id == id)
		{
			if (philo->status == 2)
				return (1);
			return (0);
		}
		philo = philo->next;
	}
	return (0);
}

int	died(t_philo_queue *queue)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		if (philo->status == 4)
			return (printf("philo %d is died\n", philo->id), 1);
		philo = philo->next;
	}
	return (0);
}

t_philo	*get_by_id(t_philo_queue *queue, int id)
{
	t_philo	*philo;

	philo = queue->first;
	while (philo)
	{
		if (philo->id == id)
			return (philo);
		philo = philo->next;
	}
	return (NULL);
}

void	*routine(void *v_queue)
{
	t_philo_queue	*queue;
	t_philo			*philo;
	static int		id;

	queue = v_queue;
	philo = get_by_id(queue, id++);
	if (!philo || id > queue->args->nb_of_philo)
		return (NULL);
	philo->last_eating = get_time(philo);
	while (!died(queue))
	{
		if (fork_available(queue, philo) && philo->last_action != 1)
		{
			pthread_mutex_lock(philo->mutex);
			if (philo->next)
				pthread_mutex_lock(philo->next->mutex);
			else
				pthread_mutex_lock(queue->first->mutex);
			eat(queue, philo);
			philo->last_action = 1;
			pthread_mutex_unlock(philo->mutex);
			if (philo->next)
				pthread_mutex_unlock(philo->next->mutex);
			else
				pthread_mutex_unlock(queue->first->mutex);
		}
		if (philo->last_action == 1)
		{
			p_sleep(queue, philo);
			philo->last_action = 2;
		}
		if (philo->last_action == 2)
		{
			think(queue, philo);
			philo->last_action = 3;
		}
		if (!check_time(philo, queue))
			break ;
	}
	return (NULL);
}
