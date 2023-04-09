/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:32:12 by hamza             #+#    #+#             */
/*   Updated: 2023/04/09 12:45:24 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * ft_usleep - sleep the program for a certain amount of time in milliseconds
 * @time: the time in milliseconds to sleep
 * Return: void
*/
void	ft_usleep(long time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(150);
}
