/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:16:36 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 19:52:07 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_philo_queue	*init_queue(void)
{
	t_philo_queue	*queue;

	queue = malloc(sizeof(t_philo_queue));
	if (!queue)
		return (NULL);
	queue->first = NULL;
	return (queue);
}

void	add_in_queue(t_philo_queue *queue, t_args *args)
{
	t_philo		*new;
	t_philo		*current;
	static int	id;

	new = malloc(sizeof(t_philo));
	if (!new)
		return ;
	new->args = args;
	new->id = id++ + 1;
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
		if (current->args && current->id == 1)
			free(current->args);
		free(current);
		current = next;
	}
	free(queue);
}

t_philo_queue	*create_philo_queue(t_args *args)
{
	t_philo_queue	*queue;
	int				i;

	i = 0;
	queue = init_queue();
	if (!queue)
		return (NULL);
	while (i < args->nb_of_philo)
	{
		add_in_queue(queue, args);
		i++;
	}
	return (queue);
}
