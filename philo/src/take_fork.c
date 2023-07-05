/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:04:11 by marvin            #+#    #+#             */
/*   Updated: 2023/07/05 15:04:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	take_left_first(t_mutex *temp, t_mutex *mutex,
	struct timeval time_start)
{
	pthread_mutex_lock(&(temp->mutex));
	print_fork(time_start, temp);
	if (temp->max > 1)
	{
		pthread_mutex_lock(&(mutex->mutex));
		print_fork(time_start, temp);
		pthread_mutex_lock(temp->print);
		if (!temp->end)
			print_action(get_p_time(time_start), temp->id_philosopher, 1);
		pthread_mutex_unlock(temp->print);
		pthread_mutex_lock(&temp->add);
		temp->time_to_die = temp->time_to_die_reset;
		pthread_mutex_unlock(&temp->add);
		ft_usleep(temp->time_to_eat);
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
		temp->eat_times++;
	}
	else
	{
		pthread_mutex_unlock(&(temp->mutex));
		usleep(temp->time_to_die * 2000);
	}
}

void	take_right_first(t_mutex *temp, t_mutex *mutex,
	struct timeval time_start)
{
	pthread_mutex_lock(&(mutex->mutex));
	print_fork(time_start, temp);
	if (temp->max > 1)
	{
		pthread_mutex_lock(&(temp->mutex));
		print_fork(time_start, temp);
		pthread_mutex_lock(temp->print);
		if (!temp->end)
			print_action(get_p_time(time_start), temp->id_philosopher, 1);
		pthread_mutex_unlock(temp->print);
		pthread_mutex_lock(&temp->add);
		temp->time_to_die = temp->time_to_die_reset;
		pthread_mutex_unlock(&temp->add);
		ft_usleep(temp->time_to_eat);
		pthread_mutex_unlock(&(mutex->mutex));
		pthread_mutex_unlock(&(temp->mutex));
		temp->eat_times++;
	}
	else
	{
		pthread_mutex_unlock(&(mutex->mutex));
		usleep(temp->time_to_die * 2000);
	}
}
