/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopheres_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:40:53 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/12 17:25:41 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	start_philos(t_philo *philo, t_infos *info)
{
	int		i;

	i = -1;
	info->start = get_time_ms();
	while (++i < info->num)
	{
		info->pid[i] = fork();
		philo[i].last_eat = get_time_ms();
		if (!info->pid[i])
		{
			while (1)
			{
				sem_wait(info->forks);
				putmsg(&philo[i], "has taken a fork", 0);
				sem_wait(info->forks);
				putmsg(&philo[i], "has taken a fork", 0);
				putmsg(&philo[i], "is eating", 0);
				if (get_time_ms() - philo[i].last_eat > info->time_to_die)
				{
					putmsg(&philo[i], "\033[31mdied\033[0m", 1);
					exit(EXIT_FAILURE);
				}
				sem_post(info->nbr_eat);
				philo[i].last_eat = get_time_ms();
				ft_usleep(info->time_to_eat);
				putmsg(&philo[i], "is sleeping", 0);
				sem_post(info->forks);
				sem_post(info->forks);
				ft_usleep(info->time_to_sleep);
				putmsg(&philo[i], "is thinking", 0);
				if (info->eat_count_max != -1 && ++philo[i].over >= info->eat_count_max)
					exit(EXIT_SUCCESS);
			}
		}
		if (i % 2 == 0)
			ft_usleep(100);
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

	i = 0;
	while (i < info->num)
	{
		philo[i].id = i;
		philo[i].over = 0;
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
int	philosopheres(t_infos *info)
{
	t_philo	*philo;
	int		status;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * info->num);
	if (!philo)
		return (write(2, "Error: malloc failed\n", 21), EXIT_FAILURE);
	if (init_philo(philo, info) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (start_philos(philo, info) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (status == 256)
		{
			while (++i < info->num)
				kill(info->pid[i], SIGKILL);
			return (EXIT_FAILURE);
		}
	}
	printf("\033[92mAll philosophers have eaten at least %d times\n\033[0m",
		info->eat_count_max);
	return (EXIT_SUCCESS);
}
