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
	int		i;
	long	start_time;

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
		pthread_mutex_init(&philo[i].check_death, NULL);
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
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(philo->lf);
		putmsg(philo, "has taken a fork");
		pthread_mutex_lock(philo->rf);
		putmsg(philo, "has taken a fork");
		putmsg(philo, "is eating");
		pthread_mutex_lock(&philo->check_death);
		philo->last_eat = get_time_ms();
		pthread_mutex_unlock(&philo->check_death);
		ft_usleep(philo->info->time_2e);
		pthread_mutex_unlock(philo->lf);
		pthread_mutex_unlock(philo->rf);
		putmsg(philo, "is thinking");
		putmsg(philo, "is eating");
		ft_usleep(philo->info->time_2s);
	}
	return (NULL);
}



int	check_death(t_philo *philo)
{
	int i;
	long	diff_time;

	i = -1;
	while (++i < philo->info->num)
	{
		pthread_mutex_lock(&philo[i].check_death);
		diff_time = get_time_ms() - philo[i].last_eat;
		pthread_mutex_unlock(&philo[i].check_death);
		if (diff_time > philo->info->time_2d)
		{
			pthread_mutex_lock(&philo[i].info->putmsg);
			printf("%zu %d is dead\n", get_time_ms() - philo->start, i + 1);
			return (1);
		}
	}
	return(0);
}

int	create_philo(t_philo *philo, int num)
{
	int			i;
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * num);
	i = -1;
	while (++i < num)
	{
		philo[i].last_eat = get_time_ms();
		pthread_create(&th[i], NULL, &philo_rotune, (void *) &philo[i]);
	}
	i = -1;
	while (!check_death(philo));
	return (EXIT_SUCCESS);
}

int	philosopheres(t_infos *info)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * info->num);
	if (!philos)
		return (write(2, "Error\nmalloc failed\n", 21), EXIT_FAILURE);
	init_philo(philos, info);
	create_philo(philos, info->num);
	return (EXIT_SUCCESS);
}
