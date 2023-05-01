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

void	iniciar_mutex(t_geral *temp)
{
	pthread_mutex_t	mutex;
	pthread_mutex_t add;

	temp->mutex->mutex = mutex;
	temp->mutex->add = add;
	pthread_mutex_init(&(temp->mutex->mutex), NULL);
	pthread_mutex_init(&(temp->mutex->add), NULL);
}

void	join_threads(t_geral **geral,pthread_t *mutex)
{
	t_geral	*temp;

	temp = *geral;
	while (temp != NULL)
	{
		pthread_join(temp->mutex->thread, NULL);
		temp = temp->next;
	}
	//pthread_join(*mutex,NULL);
}
