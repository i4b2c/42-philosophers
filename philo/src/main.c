/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:13 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int less_time_philosophers(t_geral **geral)
{
	t_geral *temp;
	long int num;
	struct timeval time_start;
	struct timeval time_end;

	temp = *geral;
	//tempo que demora para fazer isso
	gettimeofday(&time_start,NULL);
	while(temp != NULL)
	{
		temp->mutex->time_to_die--;
		temp = temp->next;
	}
	gettimeofday(&time_end,NULL);
	num = calculo(time_start,time_end);
	return num;
}

int no_time_philosophers(t_geral **geral)
{
	t_geral *temp;
	struct timeval time_start;
	struct timeval time_end;
	long int num;

	temp = *geral;
	time_start = temp->mutex->time_start;
	while(temp != NULL)
	{
		if(temp->mutex->end && temp->mutex->time_to_die < 0)
			return 1;
		if(temp->mutex->time_to_die < 0)
		{
			morreu_philosopher(temp->mutex,time_start);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void *teste(void *arg)
{
	t_geral **temp;
	long int num ;
	struct timeval time_start;

	gettimeofday(&time_start,NULL);
	temp = (t_geral **)(arg);
	while(1)
	{
		num = less_time_philosophers(temp);
		if(no_time_philosophers(temp))
			break ;
		usleep((1-num)*1000);
	}
}

int	main(int ac, char **av)
{
	t_geral	*geral;
	pthread_t life;

	geral = NULL;
	if (ac != 5 && ac != 6)
		exit_erro();
	create_lista(&geral, 1, av, ac);
	create_threads(&geral);
	pthread_create(&life,NULL,&teste,&geral);
	join_threads(&geral);
	pthread_join(life,NULL);
	destroy_all_mutex(&geral);
	close_everything(&geral);
	return (0);
}
