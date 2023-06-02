/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:04 by marvin            #+#    #+#             */
/*   Updated: 2023/06/02 12:09:36 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	pensar_init(t_mutex *temp, struct timeval time_start)
{
	struct timeval	time_end;

	gettimeofday(&time_end, NULL);
	pthread_mutex_lock(temp->print);
	if (!temp->end)
		print_action(get_p_time(time_start), temp->id_philosopher, 2);
	pthread_mutex_unlock(temp->print);
	if (temp->time_to_die < 0)
		morreu_philosopher(temp, time_start);
	ft_usleep(temp->time_to_think);
}

void	pensar(t_mutex *temp, long int temp1,
	struct timeval time_start)
{
	long int	num;
	long int	temp2;

	temp2 = get_time();
	pthread_mutex_lock(temp->print);
	if (!temp->end)
		print_action(get_p_time(time_start), temp->id_philosopher, 2);
	pthread_mutex_unlock(temp->print);
	ft_usleep(temp->time_to_think);
}

void	comer(t_mutex *temp, t_mutex *mutex,
	struct timeval time_start)
{
	long int	temp1;

	temp1 = get_time();
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
		temp->eat_times++;
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
	}
	else
		usleep(temp->time_to_die * 2000);
}

void	dormir(t_mutex *temp, struct timeval time_start)
{
	int long		num_temp;
	struct timeval	time_end;

	gettimeofday(&time_end, NULL);
	num_temp = calculo(time_start, time_end);
	pthread_mutex_lock(temp->print);
	if (!temp->end)
		print_action(get_p_time(time_start), temp->id_philosopher, 0);
	pthread_mutex_unlock(temp->print);
	ft_usleep(temp->time_to_sleep);
	if (temp->time_to_die < 0)
		morreu_philosopher(temp, time_start);
}

void	*philosopher(void *arg)
{
	int				i;
	struct timeval	time_start;
	pthread_mutex_t	*mutex_next;
	t_geral			*temp;

	i = 0;
	temp = (t_geral *)arg;
	time_start = temp->mutex->time_start;
	while (1)
	{
		if (temp->mutex->id_s == 1)
			pensar_init(temp->mutex, time_start);
		if (temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex,
				temp->next->mutex, time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex, time_start);
		dormir(temp->mutex, time_start);
		temp->mutex->id_s = 1;
		if (temp->mutex->end)
			break ;
	}
	return (NULL);
}
