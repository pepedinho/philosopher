/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:16:36 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 01:26:38 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	add_in_queue(t_philo_queue *queue)
{
	t_philo		*new;
	t_philo		*current;
	static int	id;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (0);
	new->id = id++ + 1;
	(all_to_zero(new, queue), init_mutex(new, queue));
	if (!queue)
		return (0);
	new->next = NULL;
	new->before = NULL;
	if (queue->first)
	{
		current = queue->first;
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
	else
		queue->first = new;
	queue->last = new;
	return (1);
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

static void	destroy_all_mutex(t_philo *current)
{
	pthread_mutex_destroy(current->mutex);
	pthread_mutex_destroy(current->fork_mutex);
	pthread_mutex_destroy(current->status_mutex);
	pthread_mutex_destroy(current->id_mutex);
	pthread_mutex_destroy(current->time_mutex);
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
		if (current->id == 1)
		{
			pthread_mutex_destroy(current->print_mutex);
			free(current->print_mutex);
		}
		next = current->next;
		destroy_all_mutex(current);
		(free(current->mutex), free(current->thread));
		(free(current->fork_mutex), free(current->time_mutex));
		(free(current->id_mutex), free(current->status_mutex), free(current));
		current = next;
	}
	pthread_mutex_destroy(queue->mutex_g);
	(free(queue->mutex_g), free(queue->args), free(queue));
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
		if (!add_in_queue(queue))
			return (printf("Error during create queue\n"), NULL);
		i++;
	}
	return (queue);
}
