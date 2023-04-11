/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:35:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/11 14:48:59 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * init_infos - initialize the struct info with the arguments of the program
 * @info: the struct that contains all the information
 * @av: the arguments of the program
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
static int	init_infos(t_infos *info, char **av)
{
	info->num = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->eat_count_max = ft_atoi(av[5]);
	else
		info->eat_count_max = -1;
	if (sem_init(&info->forks, 1, info->num) != 0)
		return (write(2, "Error: sem_init failed\n", 23), EXIT_FAILURE);
	if (pthread_mutex_init(&info->putmsg, NULL))
		return (write(2, "Error: mutex_init failed\n", 25), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * check_args - check if the arguments are valid
 * @ac: the number of arguments
 * @av: the arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
static int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+' && j == 0)
				j++;
			if (av[i][j] < '0' || av[i][j] > '9')
				return (EXIT_FAILURE);
			j++;
		}
		if (ft_atoi(av[i]) < 60 && i > 1 && i < 5)
			return (EXIT_FAILURE);
		i++;
	}
	if (i < 5)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * main - the main function of philo program
 * @ac: the number of arguments
 * @av: the arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	main(int ac, char **av)
{
	t_infos	info;

	if (ac < 5 || ac > 6 || check_args(ac, av))
		return (write(2, "Error: Invalid agruments\n", 24), EXIT_FAILURE);
	if (init_infos(&info, av) || philosopheres(&info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
