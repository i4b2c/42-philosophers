#ifndef HEADER_H
#define HEADER_H

#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct d_mutex
{
	int time_to_sleep;
	int time_to_die;
	int time_to_eat;
	int id_philosopher;
	int time_to_die_reset;
	int max;
	pthread_mutex_t mutex;
	pthread_mutex_t *die_mutex;
	pthread_mutex_t *print;
	pthread_t thread;
	struct d_mutex *first_mutex;
}	t_mutex;

typedef struct d_geral
{
	t_mutex *mutex;
	struct d_geral *next;
}	t_geral;

long int calculo(struct timeval s,struct timeval e);
void adicionar_na_lista(t_geral **g,t_geral *t,t_geral **u);
void create_threads(t_geral **geral);
void create_lista(t_geral **geral, int num, char **av);
void exit_erro(void);
void destroy_all_mutex(t_geral **geral);
void join_threads(t_geral **geral);
void *philosopher(void *arg);
void morreu_philosopher(t_mutex *temp);
void dormir(t_mutex *temp,struct timeval time_start);
void comer(t_mutex *t,t_mutex *m,struct timeval e);
void iniciar_mutex(t_geral *temp);


#endif
