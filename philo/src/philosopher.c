/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:04 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*
void pensar(t_mutex *temp,struct timeval time_start)
{
	long int num_temp;
	struct timeval time_end;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld the %d is thinking\n"
		,num_temp,temp->id_philosopher);
	//rand esta apenas para eu tester uma coisa
	usleep(rand () % 400*1000);
}*/

void comer(t_mutex *temp,t_mutex *mutex
	,struct timeval time_start)
{
	long int num_temp;
	long int i;
	struct timeval time_end;
	struct timeval teste1;
	struct timeval teste3;

	gettimeofday(&teste1,NULL);
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(&(temp->mutex));
	pthread_mutex_lock(&(mutex->mutex));
	gettimeofday(&teste3,NULL);
	i = calculo(teste1,teste3);
	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	if(i)
	{
		pthread_mutex_lock(temp->print);
		printf("%ld %d is thinking\n"
			,num_temp,temp->id_philosopher);
		pthread_mutex_unlock(temp->print);
		usleep(i*1000);
		//tentar ver o pensar ainda
		//temp->time_to_die -= i;
		if(temp->time_to_die <= 0)
		{
			pthread_mutex_unlock(&(temp->mutex));
			pthread_mutex_unlock(&(mutex->mutex));
			morreu_philosopher(temp);
		}
	}
	//if(temp->time_to_die < 0)
	//	morreu_philosopher(temp);
	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(temp->print);
	printf("%ld %d is eating\n"
		,num_temp,temp->id_philosopher);
	pthread_mutex_unlock(temp->print);
	temp->time_to_die -= temp->time_to_eat;
	if(temp->time_to_die <= 0)
	{
		pthread_mutex_unlock(&(temp->mutex));
		pthread_mutex_unlock(&(mutex->mutex));
		morreu_philosopher(temp);
	}
	temp->time_to_die = temp->time_to_die_reset;
	usleep(temp->time_to_eat*1000);
	pthread_mutex_unlock(&(temp->mutex));
	pthread_mutex_unlock(&(mutex->mutex));
	//if(temp->time_to_die <= 0)
	//	morreu_philosopher(temp);
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
	if(temp->time_to_die <= 0)
		morreu_philosopher(temp);
}

void morreu_philosopher(t_mutex *temp)
{
	pthread_mutex_lock((temp->die_mutex));
	pthread_mutex_lock(temp->print);
	printf("%d is died\n",temp->id_philosopher);
	//pthread_mutex_unlock(temp->print);
	//encerrar_thread(temp);
	//pthread_mutex_unlock(&(temp->die_mutex));
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
		if(temp->mutex->time_to_die <= 0)
			morreu_philosopher(temp->mutex);
		//pensar(temp->mutex,time_start);
		if(temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex
			,temp->next->mutex,time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex,time_start);
		dormir(temp->mutex,time_start);
	}
	pthread_exit(NULL);
}
