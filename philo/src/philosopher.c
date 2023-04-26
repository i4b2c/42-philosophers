/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:04 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 05:35:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


void pensar(t_mutex *temp,struct timeval time_start)
{
	long int num_temp;
	struct timeval time_end;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld the %d is thinking\n"
		,num_temp,temp->id_philosopher);
	temp->time_to_die -= temp->time_to_think;
	usleep(temp->time_to_think*1000);
}

void comer(t_mutex *temp,t_mutex *mutex
	,struct timeval time_start)
{
	long int num_temp;
	long int i;
	struct timeval time_end;
	struct timeval temp1;
	struct timeval temp2;

	num_temp = calculo(time_start,time_end);
	gettimeofday(&temp1,NULL);
	pthread_mutex_lock(&(temp->mutex));
	pthread_mutex_lock(&(mutex->mutex));
	gettimeofday(&time_end,NULL);
	gettimeofday(&temp2,NULL);
	i = calculo(temp1,temp2);
	//temp->time_to_die -= i;
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(temp->print);
	printf("%ld %d is eating\n"
		,num_temp,temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	if(i < 10)
		i = 0;
	temp->time_to_die -= temp->time_to_eat + i;
	if(temp->time_to_die < 0)
	{
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
		morreu_philosopher(temp,time_start);
	}
	printf("%ld %d is eating\n"
		,num_temp,temp->id_philosopher);
	temp->time_to_die = temp->time_to_die_reset;
	usleep(temp->time_to_eat*1000);
	pthread_mutex_unlock(&(temp->mutex));
	pthread_mutex_unlock(&(mutex->mutex));
}

void dormir(t_mutex *temp,struct timeval time_start)
{
	int long num_temp;
	struct timeval time_end;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(temp->print);
	printf("%ld %d is sleeping\n"
		,num_temp,temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	temp->time_to_die -= temp->time_to_sleep;
	usleep(temp->time_to_sleep*1000);
	if(temp->time_to_die < 0)
		morreu_philosopher(temp,time_start);
}

void morreu_philosopher(t_mutex *temp,struct timeval start)
{
	struct timeval end;
	long int num;

	gettimeofday(&end,NULL);
	num = calculo(start,end);
	pthread_mutex_lock((temp->die_mutex));
	pthread_mutex_lock(temp->print);
	printf("%ld %d is died\n",num,temp->id_philosopher);
	pthread_exit(NULL);
}

void *philosopher(void *arg)
{
	int i;
	struct timeval time_start;
	long int num;
	pthread_mutex_t *mutex_next;
	t_geral *temp;

	i = 0;
	temp = (t_geral *)arg;
	gettimeofday(&time_start,NULL);
	while(1)
	{
		if(temp->mutex->id_s == 0)
			pensar(temp->mutex,time_start);
		if(temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex
			,temp->next->mutex,time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex,time_start);
		dormir(temp->mutex,time_start);
		temp->mutex->id_s = 0;
	}
	pthread_exit(NULL);
}
