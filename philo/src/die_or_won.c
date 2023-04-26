/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_or_won.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 06:44:20 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 06:44:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void morreu_philosopher(t_mutex *temp,struct timeval start)
{
	struct timeval end;
	long int num;

	gettimeofday(&end,NULL);
	num = calculo(start,end);
	pthread_mutex_lock(temp->print);
	pthread_mutex_lock((temp->die_mutex));
	printf("%ld\t %d is died\n",num,temp->id_philosopher);
	//pthread_exit(NULL);
	exit (0);
}

void end_thread(t_mutex *temp)
{
	t_geral *geral;

	geral = *temp->inicio;
	while(geral != NULL)
	{
		geral->mutex->end = 1;
		geral = geral->next;
	}
}

void ganhou_philosopher(t_mutex *temp,struct timeval start)
{
	struct timeval end;
	long int num;

	gettimeofday(&end,NULL);
	num = calculo(start,end);
	pthread_mutex_lock(temp->print);
	pthread_mutex_lock((temp->die_mutex));
	printf("%ld\t every philosopher eat at least %d meals\n"
		,num,temp->eat_times_max);
	end_thread(temp);
	//close_everything(temp);
	pthread_mutex_unlock(temp->print);
	pthread_mutex_unlock(temp->die_mutex);
	return ;
	//exit (0);
}
