/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:15 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/05 15:45:01 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_infos
{
	int				num;
	int				time_2d;
	int				time_2e;
	int				time_2s;
	int				num_2e;
	pthread_mutex_t	*fork;

}		t_infos;

typedef struct s_philosophere
{
	int				last_eat;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
	t_infos			*info;

}	t_philo;

int	ft_atoi(const char *str);
int	philosopheres(t_philo *philo, t_infos *info);

#endif
