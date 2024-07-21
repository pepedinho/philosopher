/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:28:07 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 22:05:22 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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
	thread_generation(queue);
	free_queue(queue);
	return (EXIT_SUCCESS);
}
