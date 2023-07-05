/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:07:20 by marvin            #+#    #+#             */
/*   Updated: 2023/07/05 15:05:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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
	pthread_mutex_t	add;
	pthread_t		thread;
	struct d_mutex	*first_mutex;
	struct d_geral	**inicio;
	struct timeval	time_start;
}					t_mutex;

typedef struct d_geral
{
	t_mutex			*mutex;
	struct d_geral	*next;
}					t_geral;

/**************\
|**--CREATE--**|
\**************/
void		adicionar_na_lista(t_geral **g, t_geral *t);
void		get_info_lista(t_geral *temp, char **av, int ac, int i);
void		start_lista(pthread_mutex_t **d, pthread_mutex_t **p);
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
void		free_lista(int i, t_geral *g, t_mutex *mutex, t_geral *geral);
int			check_eat_philosophers(t_geral **temp);
void		close_everything(t_geral **temp);

/*************\
|**--EXTRA--**|
\*************/
int			ft_atoi(const char *string);
void		print_fork(struct timeval time_start, t_mutex *temp);
void		print_action(long num, int philo, int op);

/************\
|**--INIT--**|
\************/
void		iniciar_mutex(t_geral *temp);
void		join_threads(t_geral **geral, pthread_t *mutex);

/************\
|**--LIFE--**|
\************/
long int	less_time_philosophers(t_geral **geral);
int			no_time_philosophers(t_geral **geral);
void		*life_philosopher(void *arg);

/********************\
|**--PHILOSOPHERS--**|
\********************/
void		pensar_init(t_mutex *temp, struct timeval start);
void		pensar(t_mutex *temp, long int temp1, struct timeval time_start);
void		dormir(t_mutex *temp, struct timeval time_start);
void		comer(t_mutex *t, t_mutex *m, struct timeval e);
void		*philosopher(void *arg);

/************\
|**--TIME--**|
\************/
long int	get_p_time(struct timeval time_start);
long int	get_time(void);
void		ft_usleep(int time);
long int	calculo(struct timeval s, struct timeval e);

/************\
|**--ERRO--**|
\************/
int			check_error(char **av, int ac);

/*****************\
|**--TAKE_FORK--**|
\*****************/
void		take_right_first(t_mutex *t, t_mutex *m, struct timeval ts);
void		take_left_first(t_mutex *t, t_mutex *m, struct timeval ts);

#endif
