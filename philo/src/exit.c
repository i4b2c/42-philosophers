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

void	exit_erro(void)
{
	printf("number_of_philosophers  ");
	printf("time_to_die  time_to_eat  time_to_sleep  ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit (0);
}

void	destroy_all_mutex(t_geral **geral)
{
	t_geral	*temp;

	temp = *geral;
	while (temp != NULL)
	{
		pthread_mutex_destroy(&(temp->mutex->mutex));
		temp = temp->next;
	}
}

int	check_eat_philosophers(t_geral **temp)
{
	t_geral	*geral;

	geral = *temp;
	while (geral != NULL)
	{
		if (geral->mutex->eat_times < geral->mutex->eat_times_max)
			return (0);
		geral = geral->next;
	}
	return (1);
}

void	free_lista(int i, t_geral *g, t_mutex *mutex, t_geral *geral)
{
	if (i)
	{
		free(mutex);
		free(g);
	}
	else
	{
		free((geral->mutex->die_mutex));
		free((geral->mutex->print));
	}
}

void	close_everything(t_geral **temp)
{
	t_geral	*geral;
	t_geral	*temp_freeg;
	t_mutex	*temp_free;
	int		i;

	i = 0;
	geral = *temp;
	while (geral != NULL)
	{
		free_lista(i, temp_freeg, temp_free, geral);
		temp_free = geral->mutex;
		temp_freeg = geral;
		geral = geral->next;
		i++;
	}
	free(temp_free);
	free(temp_freeg);
	free(geral);
	return ;
}
