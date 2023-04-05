/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:23:21 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/05 15:45:15 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_infos *info)
{
	int	i;

	i = -1;
	while (++i < info->num)
		pthread_mutex_init(info[i].fork, NULL);
	return (EXIT_SUCCESS);
}

int	init_infos(t_infos *info, char **av)
{
	info->num = ft_atoi(av[1]);
	info->time_2d = ft_atoi(av[2]);
	info->time_2e = ft_atoi(av[3]);
	info->time_2s = ft_atoi(av[4]);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num);
	if (!info->fork)
		return (write(1, "Error\nmallco flaid\n", 2), exit(EXIT_FAILURE), 1);
	if (av[5])
		info->num_2e = ft_atoi(av[5]);
	return ((!info->num || !info->time_2d || !info->time_2e || !info->time_2s));
}

int	main(int ac, char **av)
{
	t_infos	info;

	if (ac <= 5 || !av[1] || !av[2] || !av[3] || !av[4]
		|| init_infos(&info, av))
		return (write(1, "Error\nInvalid agrument\n", 2), EXIT_FAILURE);
	init_mutex(&info);
	philosopheres()
}
