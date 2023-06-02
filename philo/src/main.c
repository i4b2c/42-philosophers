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

int	main(int ac, char **av)
{
	t_geral		*geral;
	pthread_t	life;

	geral = NULL;
	if (ac != 5 && ac != 6)
		exit_erro();
	if (check_error(av, ac))
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	create_lista(&geral, 1, av, ac);
	create_threads(&geral);
	pthread_create(&life, NULL,
		&life_philosopher, &geral);
	join_threads(&geral, &life);
	pthread_join(life, NULL);
	destroy_all_mutex(&geral);
	close_everything(&geral);
	return (0);
}
