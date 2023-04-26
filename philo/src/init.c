/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:17 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void iniciar_mutex(t_geral *temp)
{
	pthread_mutex_t mutex;
	temp->mutex->mutex = mutex;
	pthread_mutex_init(&(temp->mutex->mutex),NULL);
}

void join_threads(t_geral **geral)
{
	t_geral *temp;

	temp = *geral;
	while(temp != NULL)
	{
		pthread_join(temp->mutex->thread,NULL);
		temp = temp->next;
	}
}
