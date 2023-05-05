/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:04 by marvin            #+#    #+#             */
/*   Updated: 2023/05/05 18:56:36 by marvin           ###   ########.fr       */
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


void	pensar_init(t_mutex *temp, struct timeval time_start)
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

void pensar(t_mutex *temp,long int temp1,long int temp2,struct timeval time_start)
{
	long int num;

	num = temp2 - temp1;
	num /= 1000;
	if(num >= 10)
	//if(num)
	{
		pthread_mutex_lock(temp->print);
		printf("%ld\t %d is thinking\n",
			get_p_time(time_start), temp->id_philosopher);
		pthread_mutex_unlock(temp->print);
		ft_usleep(num);
	}
}

void	comer(t_mutex *temp, t_mutex *mutex,
	struct timeval time_start)
{
	long int temp1,temp2;
	temp1 = get_time();
	pthread_mutex_lock(&(temp->mutex));
	print_fork(time_start, temp);
	if(temp->max != 1)
	{
		pthread_mutex_lock(&(mutex->mutex));
		print_fork(time_start, temp);
		temp2 = get_time();
		pensar(temp,temp1,temp2,time_start);
		pthread_mutex_lock(temp->print);
		if(!temp->end)
			printf("%ld\t %d is eating\n",
				get_p_time(time_start), temp->id_philosopher);
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
		usleep(temp->time_to_die*2000);
	//temp2 = get_time();
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
			pensar_init(temp->mutex, time_start);
		if (temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex,
				temp->next->mutex, time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex, time_start);
		dormir(temp->mutex, time_start);
		if (temp->mutex->time_to_die <= 0)
			morreu_philosopher(temp->mutex, time_start);
		temp->mutex->id_s = 1;
		if (temp->mutex->end)
			break ;
	}
	return (NULL);
}
