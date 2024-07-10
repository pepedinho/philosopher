/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:16:36 by itahri            #+#    #+#             */
/*   Updated: 2024/07/10 23:44:42 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <pthread.h>

t_philo_queue	*init_queue(t_args *args)
{
	t_philo_queue	*queue;

	queue = malloc(sizeof(t_philo_queue));
	if (!queue)
		return (NULL);
	queue->args = args;
	queue->mutex_g = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(queue->mutex_g, NULL);
	queue->first = NULL;
	return (queue);
}

void	init_mutex(t_philo *new, t_philo_queue *queue)
{
	new->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->mutex, NULL);
	if (!new->mutex)
		free_queue(queue);
	new->print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->print_mutex, NULL);
	if (!new->print_mutex)
		free_queue(queue);
	new->fork_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->fork_mutex, NULL);
	if (!new->fork_mutex)
		free_queue(queue);
	new->status_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->status_mutex, NULL);
	if (!new->status_mutex)
		free_queue(queue);
	new->id_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->id_mutex, NULL);
	if (!new->id_mutex)
		free_queue(queue);
	new->time_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->time_mutex, NULL);
	if (!new->time_mutex)
		free_queue(queue);
}
int	add_in_queue(t_philo_queue *queue)
{
	t_philo		*new;
	t_philo		*current;
	static int	id;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (0);
	new->id = id++ + 1;
	new->status = 0;
	new->starting_time = 0;
	new->last_action = 0;
	new->last_eating = 0;
	new->thread = malloc(sizeof(pthread_t));
	if (!new->thread)
		free_queue(queue);
	init_mutex(new, queue);
	if (!queue)
		return (0);
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
		pthread_mutex_destroy(current->print_mutex);
		pthread_mutex_destroy(current->fork_mutex);
		pthread_mutex_destroy(current->status_mutex);
		pthread_mutex_destroy(current->id_mutex);
		pthread_mutex_destroy(current->time_mutex);
		free(current->mutex);
		free(current->print_mutex);
		free(current->thread);
		free(current);
		current = next;
	}
	pthread_mutex_destroy(queue->mutex_g);
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
		if (!add_in_queue(queue))
			return (printf("Error during create queue\n"), NULL);
		i++;
	}
	return (queue);
}
