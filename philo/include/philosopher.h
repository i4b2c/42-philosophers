/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:07:20 by marvin            #+#    #+#             */
/*   Updated: 2023/05/01 06:15:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#define M t_mutex
#define G t_geral
#define TM struct timeval

# include <stddef.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct d_mutex
{
	int				ac;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				id_philosopher;
	int				time_to_die_reset;
	int				eat_times;
	int				eat_times_max;
	int				end;
	int				id_s;
	int				max;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t add;
	pthread_t		thread;
	struct d_mutex	*first_mutex;
	struct d_geral	**inicio;
	struct timeval time_start;
}					t_mutex;

typedef struct d_geral
{
	t_mutex			*mutex;
	struct d_geral	*next;
}					t_geral;


/****************\
|**--ADD_LIST--**|
\****************/
void		adicionar_na_lista(t_geral **g, t_geral *t, t_geral **u);

/**************\
|**--CREATE--**|
\**************/
void		create_lista(t_geral **geral, int num, char **av, int ac);
void		create_threads(t_geral **geral);

/******************\
|**--DIE_OR_WON--**|
\******************/
void		morreu_philosopher(t_mutex *temp, struct timeval start);
void		end_thread(t_mutex *temp);
void		ganhou_philosopher(t_mutex *temp, struct timeval start);

/************\
|**--EXIT--**|
\************/
void		exit_erro(void);
void		destroy_all_mutex(t_geral **geral);
int			check_eat_philosophers(t_mutex *temp);
void		close_everything(t_geral **temp);

/*************\
|**--EXTRA--**|
\*************/
int			ft_atoi(const char *string);

/************\
|**--INIT--**|
\************/
void		iniciar_mutex(t_geral *temp);
void		join_threads(t_geral **geral,pthread_t *mutex);

/********************\
|**--PHILOSOPHERS--**|
\********************/
void		pensar(t_mutex *temp, struct timeval start);
void		dormir(t_mutex *temp, struct timeval time_start);
void		comer(t_mutex *t, t_mutex *m, struct timeval e);
void		*philosopher(void *arg);

/************\
|**--TIME--**|
\************/
void		ft_usleep_micro(float time);
long int	get_p_time(struct timeval time_start);
long int	get_time(void);
void		ft_usleep(int time);
long int	calculo(struct timeval s, struct timeval e);

#endif
