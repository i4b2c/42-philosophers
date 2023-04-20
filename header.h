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
	pthread_mutex_t mutex;
	pthread_t thread;
}	t_mutex;

typedef struct d_geral
{
	t_mutex *mutex;
	struct d_geral *next;
}	t_geral;

#endif
