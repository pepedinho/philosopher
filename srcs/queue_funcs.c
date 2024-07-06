/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:16:36 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:25:47 by itahri           ###   ########.fr       */
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
	queue->first = NULL;
	return (queue);
}

void	add_in_queue(t_philo_queue *queue)
{
	t_philo		*new;
	t_philo		*current;
	static int	id;

	new = malloc(sizeof(t_philo));
	if (!new)
		return ;
	new->id = id++ + 1;
	new->status = 0;
	new->starting_time = 0;
	new->last_action = 0;
	new->last_eating = 0;
	new->thread = malloc(sizeof(pthread_t));
	if (!new->thread)
		free_queue(queue);
	new->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->mutex, NULL);
	if (!new->mutex)
		free_queue(queue);
	new->next = NULL;
	if (queue->first)
	{
		current = queue->first;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		queue->first = new;
}

void	get_out_queue(t_philo_queue *queue)
{
	t_philo	*current;

	if (!queue)
		return ;
	if (queue->first)
	{
		current = queue->first;
		queue->first = current->next;
		free(current);
	}
}

void	free_queue(t_philo_queue *queue)
{
	t_philo	*current;
	t_philo	*next;

	if (!queue)
		return ;
	current = queue->first;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(current->mutex);
		free(current->mutex);
		free(current->thread);
		free(current);
		current = next;
	}
	free(queue->args);
	free(queue);
	queue = NULL;
}

t_philo_queue	*create_philo_queue(t_args *args)
{
	t_philo_queue	*queue;
	int				i;

	i = 0;
	queue = init_queue(args);
	if (!queue)
		return (NULL);
	while (i < args->nb_of_philo)
	{
		add_in_queue(queue);
		if (!queue)
			return (printf("Error during create queue\n"), NULL);
		i++;
	}
	return (queue);
}