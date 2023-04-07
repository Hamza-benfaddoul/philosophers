/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:15 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/07 15:07:10 by hbenfadd         ###   ########.fr       */
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
	int				nbr_of_t2e;
	pthread_mutex_t	*fork;
	pthread_mutex_t	putmsg;

}		t_infos;

typedef struct s_philosophere
{
	int				id;
	size_t			start;
	int				last_eat;
	pthread_mutex_t	check_death;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
	t_infos			*info;

}	t_philo;

int		ft_atoi(const char *str);
int		philosopheres(t_infos *info);
long	get_time_ms(void);
void	ft_usleep(long time);
size_t	ft_strlen(const char *s);

#endif
