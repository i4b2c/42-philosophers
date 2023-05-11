/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:09 by marvin            #+#    #+#             */
/*   Updated: 2023/04/28 12:27:43 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int	get_p_time(struct timeval time_start)
{
	long int	temp;
	long int	temp2;

	temp2 = ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000));
	temp = get_time();
	return (temp - temp2);
}

long int	get_time(void)
{
	struct timeval	time_start;
	long int		temp;

	gettimeofday(&time_start, NULL);
	temp = ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000));
	return (temp);
}

void	ft_usleep(int time)
{
	long int	temp;

	temp = get_time();
	while (get_time() < temp + time)
		usleep(10);
}

long int	calculo(struct timeval time_start, struct timeval time_end)
{
	long int	temp;

	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000)
			- (time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return (temp);
}
