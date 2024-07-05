/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:28:07 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 19:47:59 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	display_queue(t_philo_queue *queue)
{
	t_philo	*current;

	current = queue->first;
	while (current)
	{
		printf("----------------------------------------------\n");
		printf("arg1 : %d\n", current->args->nb_of_philo);
		printf("arg2 : %d\n", current->args->time_to_die);
		printf("arg3 : %d\n", current->args->time_to_eat);
		printf("arg4 : %d\n", current->args->time_to_sleep);
		printf("arg5 : %d\n", current->args->itteration);
		printf("id : %d\n", current->id);
		printf("----------------------------------------------\n");
		current = current->next;
	}
}

int	main(int argc, const char *argv[])
{
	t_args			*args;
	t_philo_queue	*queue;

	if (argc < 5)
		return ((printf("Error Invalid args\n"), -1));
	args = check_args(argc, argv);
	if (!args)
		return (printf("error\n"), -1);
	queue = create_philo_queue(args);
	if (!queue)
		return (printf("error\n"), -1);
	display_queue(queue);
	free_queue(queue);
	return (EXIT_SUCCESS);
}
