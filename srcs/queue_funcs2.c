/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:04:39 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 04:11:11 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_philo_queue	*init_queue(t_args *args)
{
	t_philo_queue	*queue;

	queue = malloc(sizeof(t_philo_queue));
	if (!queue)
		return (NULL);
	queue->args = args;
	queue->mutex_g = malloc(sizeof(pthread_mutex_t));
	queue->stop_monitoring = 0;
	pthread_mutex_init(queue->mutex_g, NULL);
	queue->first = NULL;
	return (queue);
}

void	init_re(t_philo *elem, t_philo_queue *queue)
{
	elem->status_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(elem->status_mutex, NULL);
	if (!elem->status_mutex)
		free_queue(queue);
	elem->id_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(elem->id_mutex, NULL);
	if (!elem->id_mutex)
		free_queue(queue);
	elem->time_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(elem->time_mutex, NULL);
	if (!elem->time_mutex)
		free_queue(queue);
}

void	init_mutex(t_philo *elem, t_philo_queue *queue)
{
	static int		i;
	pthread_mutex_t	*p_mutex;

	i++;
	if (i == 1)
	{
		p_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(p_mutex, NULL);
		if (!p_mutex)
			free_queue(queue);
		elem->print_mutex = p_mutex;
	}
	else
		elem->print_mutex = queue->first->print_mutex;
	elem->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(elem->mutex, NULL);
	if (!elem->mutex)
		free_queue(queue);
	elem->fork_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(elem->fork_mutex, NULL);
	if (!elem->fork_mutex)
		free_queue(queue);
	init_re(elem, queue);
}

void	all_to_zero(t_philo *elem, t_philo_queue *queue)
{
	elem->status = 0;
	elem->starting_time = 0;
	elem->last_action = 0;
	elem->last_eating = 0;
	elem->is_limmited_by_it = 0;
	elem->itteration = queue->args->itteration;
	if (elem->itteration)
		elem->is_limmited_by_it = 1;
	elem->thread = malloc(sizeof(pthread_t));
	if (!elem->thread)
		free_queue(queue);
}
