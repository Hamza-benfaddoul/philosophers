/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:42:21 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/09 12:11:14 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * putmsg - print the message of the philosopher with the time and the id
 * @philo: the struct that contains all the information of the philosopher
 * @action: the action of the philosopher (is eating, is sleeping, is thinking)
 * @flag: if the philosopher is overeating
 * Return: void
*/
void	putmsg(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->info->putmsg);
	printf("%zu %d %s\n", get_time_ms() - philo->start, philo->id + 1, action);
	pthread_mutex_unlock(&philo->info->putmsg);
}
