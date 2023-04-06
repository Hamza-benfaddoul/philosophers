/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:29:23 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/06 15:22:04by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, t_infos *info)
{
	int	i;
	size_t start_time;

	start_time = get_time_ms();

	i = -1;
	while (++i < info->num)
	{
		philo[i].id = i;
		philo[i].last_eat = 0;
		philo[i].rf = &info->fork[(i + 1) % info->num];
		philo[i].lf = &info->fork[i];
		philo[i].info = info;
		philo[i].start = start_time;
	}
	return (EXIT_SUCCESS);
}

void	putmsg(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->info->putmsg);
	printf("%zu %d %s\n", get_time_ms() - philo->start, philo->id + 1, action);
	pthread_mutex_unlock(&philo->info->putmsg);
}

void	*philo_rotune(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(philo->lf);
		putmsg(philo, "has taken a fork");
		pthread_mutex_lock(philo->rf);
		putmsg(philo, "has taken a fork");
		putmsg(philo, "is eating");
		usleep(philo->info->time_2e * 1000);
		pthread_mutex_unlock(philo->lf);
		pthread_mutex_unlock(philo->rf);
	}
	return (NULL);
}

int	create_philo(t_philo *philo, int num)
{
	int			i;
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * num);
	i = -1;
	while (++i < num)
	{
		pthread_create(&th[i], NULL, &philo_rotune, (void *) &philo[i]);
		usleep(100);
	}
	i = -1;
	while (++i < num)
		pthread_join(th[i], NULL);
	return (EXIT_SUCCESS);
}

int	philosopheres(t_infos *info)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * info->num);
	if (!philos)
		return (write(2, "Error\nmalloc failed\n", 22), EXIT_FAILURE);
	init_philo(philos, info);
	create_philo(philos, info->num);
	return (EXIT_SUCCESS);
}
