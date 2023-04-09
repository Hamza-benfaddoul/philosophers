/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:15 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/09 12:39:48 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_infos
{
	int				num;
	int				time_2d;
	int				time_2e;
	int				time_2s;
	int				nbr_t2e;
	int				overeat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	putmsg;

}		t_infos;

typedef struct s_philosophere
{
	int				id;
	size_t			start;
	long			last_eat;
	int				is_eaten;
	pthread_mutex_t	check_death;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
	t_infos			*info;

}	t_philo;

void	putmsg(t_philo *philo, char *action);
int		philosopheres(t_infos *info);
int		ft_atoi(const char *str);
void	ft_usleep(long time);
long	get_time_ms(void);

#endif