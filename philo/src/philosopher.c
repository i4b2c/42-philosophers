/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:04 by marvin            #+#    #+#             */
/*   Updated: 2023/04/28 14:06:15 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	print_fork(struct timeval time_start, t_mutex *temp)
{
	pthread_mutex_lock((temp->print));
	if(!temp->end)
		printf("%ld\t %d has taken a fork\n"
			,get_p_time(time_start),temp->id_philosopher);
	pthread_mutex_unlock((temp->print));
}

void	pensar(t_mutex *temp, struct timeval time_start)
{
	//long int		num_temp;
	struct timeval	time_end;

	gettimeofday(&time_end, NULL);
	//num_temp = calculo(time_start, time_end);
	pthread_mutex_lock(temp->print);
	if(!temp->end)
		printf("%ld\t %d is thinking\n",
			get_p_time(time_start), temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	if (temp->time_to_die < 0)
		morreu_philosopher(temp, time_start);
	ft_usleep(temp->time_to_think);
}

void	comer(t_mutex *temp, t_mutex *mutex,
	struct timeval time_start)
{
	long int		i;
	struct timeval	time_end;
	struct timeval	temp1;

	gettimeofday(&temp1, NULL);
	pthread_mutex_lock(&(temp->mutex));
	print_fork(time_start, temp);
	pthread_mutex_lock(&(mutex->mutex));
	print_fork(time_start, temp);
	gettimeofday(&time_end, NULL);
	i = calculo(temp1,time_end);
	if (temp->time_to_die < 0)
	{
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
		morreu_philosopher(temp, time_start);
	}
	pthread_mutex_lock(temp->print);
	if(!temp->end)
		printf("%ld\t %d is eating\n",
			get_p_time(time_start), temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	temp->eat_times++;
	temp->time_to_die = temp->time_to_die_reset;
	if (check_eat_philosophers(temp) && temp->ac == 6)
	{
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
		ganhou_philosopher(temp, time_start);
	}
	ft_usleep(temp->time_to_eat);
	pthread_mutex_unlock(&(temp->mutex));
	pthread_mutex_unlock(&(mutex->mutex));
}

void	dormir(t_mutex *temp, struct timeval time_start)
{
	int long		num_temp;
	struct timeval	time_end;

	gettimeofday(&time_end, NULL);
	num_temp = calculo(time_start, time_end);
	pthread_mutex_lock(temp->print);
	if(!temp->end)
		printf("%ld\t %d is sleeping\n",
			num_temp, temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	ft_usleep(temp->time_to_sleep);
	if (temp->time_to_die < 0)
		morreu_philosopher(temp, time_start);
}

void	*philosopher(void *arg)
{
	int				i;
	struct timeval	time_start;
	long int		num;
	pthread_mutex_t	*mutex_next;
	t_geral			*temp;

	i = 0;
	temp = (t_geral *)arg;
	time_start = temp->mutex->time_start;
	while (1)
	{
		if (temp->mutex->id_s == 0)
			pensar(temp->mutex, time_start);
		if (temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex,
				temp->next->mutex, time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex, time_start);
		dormir(temp->mutex, time_start);
		if (temp->mutex->time_to_die <= 0)
			morreu_philosopher(temp->mutex, time_start);
		temp->mutex->id_s = 0;
		if (temp->mutex->end)
			break ;
	}
	return (NULL);
}
