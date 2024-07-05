/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:31:40 by itahri            #+#    #+#             */
/*   Updated: 2024/07/05 18:58:12 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	is_negative;

	i = 0;
	result = 0;
	is_negative = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (is_negative)
		result = -result;
	return (result);
}

void	fill_corresponding_arg(t_args *args, const char **argv, int i)
{
	if (i == 1)
		args->nb_of_philo = ft_atoi(argv[i]);
	else if (i == 2)
		args->time_to_die = ft_atoi(argv[i]);
	else if (i == 3)
		args->time_to_eat = ft_atoi(argv[i]);
	else if (i == 4)
		args->time_to_sleep = ft_atoi(argv[i]);
	if (i == 5)
		args->itteration = ft_atoi(argv[i]);
	else
		args->itteration = 0;
}

t_args	*check_args(int argc, const char **argv)
{
	int		i;
	int		j;
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (free(args), NULL);
			j++;
		}
		fill_corresponding_arg(args, argv, i);
		i++;
	}
	return (args);
}
