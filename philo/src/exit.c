/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:21 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void exit_erro(void)
{
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep\n");
	exit (0);
}

void destroy_all_mutex(t_geral **geral)
{
	t_geral *temp;

	temp = *geral;
	while(temp != NULL)
	{
		pthread_mutex_destroy(&(temp->mutex->mutex));
		temp = temp->next;
	}
}
