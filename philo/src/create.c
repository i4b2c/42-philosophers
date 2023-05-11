/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:25 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	adicionar_na_lista(t_geral **g, t_geral *t)
{
	t_geral	*new;

	if (!(*g))
	{
		*g = t;
		return ;
	}
	new = *g;
	while (new->next != NULL)
		new = new->next;
	new->next = t;
}

void	get_info_lista(t_geral *temp, char **av, int ac, int i)
{
	if (!(i % 2))
		temp->mutex->id_s = 0;
	else
		temp->mutex->id_s = 1;
	temp->mutex->max = ft_atoi(av[1]);
	temp->mutex->ac = ac;
	temp->mutex->time_to_die = ft_atoi(av[2]);
	temp->mutex->time_to_die_reset = ft_atoi(av[2]);
	temp->mutex->time_to_eat = ft_atoi(av[3]);
	temp->mutex->time_to_sleep = ft_atoi(av[4]);
	temp->mutex->time_to_think = ft_atoi(av[2])
		- (ft_atoi(av[3]) + ft_atoi(av[4]));
	if (temp->mutex->time_to_think < 0)
		temp->mutex->time_to_think = 0;
	temp->mutex->end = 0;
	temp->mutex->eat_times = 0;
	temp->mutex->id_philosopher = i;
	if (ac == 6)
		temp->mutex->eat_times_max = ft_atoi(av[5]);
	else
		temp->mutex->eat_times_max = -1;
}

void	start_lista(pthread_mutex_t **d, pthread_mutex_t **p)
{
	*d = malloc(sizeof(pthread_mutex_t));
	*p = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(*d, NULL);
	pthread_mutex_init(*p, NULL);
}

void	create_lista(t_geral **geral, int i, char **av, int ac)
{
	t_geral			*temp;
	t_mutex			*mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*print;
	struct timeval	time_start;

	start_lista(&die_mutex, &print);
	gettimeofday(&time_start, NULL);
	while (i <= ft_atoi(av[1]))
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		temp->mutex->time_start = time_start;
		get_info_lista(temp, av, ac, i);
		temp->mutex->inicio = geral;
		iniciar_mutex(temp);
		if (i == 1)
			mutex = temp->mutex;
		temp->mutex->first_mutex = mutex;
		temp->next = NULL;
		temp->mutex->die_mutex = die_mutex;
		temp->mutex->print = print;
		adicionar_na_lista(geral, temp);
		i++;
	}
}

void	create_threads(t_geral **geral)
{
	t_geral	*temp_geral;

	temp_geral = *geral;
	while (temp_geral != NULL)
	{
		pthread_create(&(temp_geral->mutex->thread), NULL,
			&philosopher, temp_geral);
		temp_geral = temp_geral->next;
	}
}
