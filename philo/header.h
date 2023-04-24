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

typedef struct s_info
{
	int time_total;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	pthread_mutex_t fork;
	pthread_mutex_t next;
	pthread_mutex_t die;
}	t_info;

typedef struct s_philo
{
	unsigned int id;
	unsigned int id_max;
	pthread_t thread_id;
	struct s_info *info;
}	t_philo;

typedef struct s_geral
{
	t_philo *philo;
	//t_info info;
}	t_geral;

#endif
