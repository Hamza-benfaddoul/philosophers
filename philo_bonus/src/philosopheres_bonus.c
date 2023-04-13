/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopheres_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:40:53 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/13 14:12:03 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * chekc_death - check if the philosophers are dead
 * @arg: the struct that contains all the information about the philosophers
 * Return: void
*/
void	*check_death(void *arg)
{
	t_philo	*philo;
	long	l_eat;

	philo = (t_philo *)arg;
	while (1)
	{
		l_eat = philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000;
		if (get_time_ms() - l_eat > philo->info->time_to_die)
		{
			putmsg(philo, "\033[31mdied\033[0m", 1);
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

/**
 * philo_routine - the routine of the philosophers (eat, sleep, think)
 	and check if they are dead or not (if they have eaten enough)
 * @philo: the struct that contains all the information about the philosophers
 * Return: void
*/
void	philo_routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->info->forks);
		putmsg(philo, "has taken a fork", 0);
		sem_wait(philo->info->forks);
		putmsg(philo, "has taken a fork", 0);
		putmsg(philo, "is eating", 0);
		gettimeofday(&philo->last_eat, NULL);
		ft_usleep(philo->info->time_to_eat);
		putmsg(philo, "is sleeping", 0);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		ft_usleep(philo->info->time_to_sleep);
		if (philo->info->eat_max != -1 && ++philo->over >= philo->info->eat_max)
			exit(EXIT_SUCCESS);
		putmsg(philo, "is thinking", 0);
	}
}

static int	start_philos(t_philo *philo, t_infos *info)
{
	int			i;
	pthread_t	thread;

	i = -1;
	info->start = get_time_ms();
	while (++i < info->num)
	{
		info->pid[i] = fork();
		gettimeofday(&philo[i].last_eat, NULL);
		if (!info->pid[i])
		{
			pthread_create(&thread, NULL, &check_death, &philo[i]);
			philo_routine(&philo[i]);
		}
	}
	return (EXIT_SUCCESS);
}

/**
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

/**
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
	if (init_philo(philo, info) || start_philos(philo, info))
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
	if (ECHILD != errno && info->eat_max != -1)
		return (write(2, "Error: waitpid failed\n", 22), EXIT_FAILURE);
	else if (info->eat_max != -1)
		printf("\033[92mAll philosophers have eaten at least %d times\n\033[0m",
			info->eat_max);
	return (EXIT_SUCCESS);
}
