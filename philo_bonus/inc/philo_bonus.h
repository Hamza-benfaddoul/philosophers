/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:33:06 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/12 17:25:27 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <string.h>

typedef struct s_infos
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	pthread_t		*check_nbr_eat;
	sem_t			*nbr_eat;
	pid_t			*pid;
	long			start;
	sem_t			*putmsg;
	sem_t			*forks;
}	t_infos;

typedef struct s_philo
{
	int		id;
	long	last_eat;
	int		over;
	t_infos	*info;
}	t_philo;

void	putmsg(t_philo *philo, char *action, int is_done);
int		philosopheres(t_infos *info);
int		ft_atoi(const char *str);
void	ft_usleep(long time);
long	get_time_ms(void);

#endif