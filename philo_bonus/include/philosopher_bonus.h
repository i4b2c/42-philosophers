/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:07:20 by marvin            #+#    #+#             */
/*   Updated: 2023/07/31 18:39:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stddef.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct d_data
{
	int id;
	int time_to_sleep;
	int time_to_think;
	int time_to_eat;
	int time_to_die;
	pid_t pid;
}		t_data;

typedef struct d_philo
{
	t_data *data;
	struct d_philo *next;
}		t_philo;

#endif
