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

int main(int ac, char **av)
{
	int num;
	t_geral *geral;

	geral = NULL;
	if(ac != 5 && ac != 6)
		exit_erro();
	num = atoi(av[1]);
	create_lista(&geral,num,av,ac);
	create_threads(&geral);
	join_threads(&geral);
	destroy_all_mutex(&geral);
	close_everything(&geral);
	return 0;
}
