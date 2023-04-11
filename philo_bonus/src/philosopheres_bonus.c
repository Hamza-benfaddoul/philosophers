/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopheres_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:40:53 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/11 14:40:47 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	start_philos(t_philo *philo, t_infos *info)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < info->num)
	{
		pid = fork();
		if (!pid)
		{
			while (1)
			{
				sem_wait(&info->forks);
				putmsg(philo, "has taken a fork", 0);
				sem_wait(&info->forks);
				putmsg(philo, "has taken a fork", 0);
				putmsg(philo, "is eating", 0);
				ft_usleep(info->time_to_eat);
				sem_post(&info->forks);
				sem_post(&info->forks);
				putmsg(philo, "is sleeping", 0);
				ft_usleep(info->time_to_sleep);
				putmsg(philo, "is thinking", 0);
			}
		}
	}
	return (EXIT_SUCCESS);
}

/*
* init_philo - initialize the philosophers
* @philo: the struct that contains all the information about the philosophers
* @info: the struct that contains all the information about the program
* Return: EXIT_SUCCESS or EXIT_FAILURE
*/
static int	init_philo(t_philo *philo, t_infos *info)
{
	int	i;
	int	start_time;

	start_time = get_time_ms();
	i = 0;
	while (i < info->num)
	{
		philo[i].id = i + 1;
		philo[i].start = start_time;
		philo[i].info = info;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
* philosophers - create the philosophers 
* @info: the struct that contains all the information about the program
* Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	philosophers(t_infos *info)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * info->num);
	if (!philo)
		return (write(2, "Error: malloc failed\n", 21), EXIT_FAILURE);
	if (init_philo(philo, info) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (start_philos(philo, info) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
