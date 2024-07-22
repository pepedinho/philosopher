/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:28:26 by itahri            #+#    #+#             */
/*   Updated: 2024/07/22 01:28:43 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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
