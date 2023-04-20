#include "header.h"

void iniciar_mutex(t_geral *temp)
{
	pthread_mutex_t mutex;
	temp->mutex->mutex = mutex;
	pthread_mutex_init(&(temp->mutex->mutex),NULL);
}

long int calculo(struct timeval time_start, struct timeval time_end)
{
	long int temp;

	//ta a funcionar o contador em milisegundos
	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000) -
    		(time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return temp;
}

void *teste(void *arg)
{
	int i;
	struct timeval time_end;
	struct timeval time_start;
	long int num;
	t_mutex *temp;
	pthread_mutex_t mutex;

	i = 0;
	temp = (t_mutex *)arg;
	mutex = temp->mutex;
	gettimeofday(&time_start,NULL);
	if(temp->time_to_eat < temp->time_to_sleep)
	{	
		while(1)
		{
			//pthread_mutex_lock(mutex);
			gettimeofday(&time_end,NULL);
			printf("%ld philosopho %d esta a comer\n"
				,calculo(time_start,time_end)
				,temp->id_philosopher);
			usleep(temp->time_to_eat);
			//pthread_mutex_unlock(mutex);
		}
	}
	else
	{
		while(1)
		{
			//pthread_mutex_lock(mutex);
			gettimeofday(&time_end,NULL);
			printf("%ld philosopho %d esta a dormir\n"
				,calculo(time_start,time_end)
				,temp->id_philosopher);
			usleep(temp->time_to_sleep);
			//pthread_mutex_unlock(mutex);
		}
	}
	pthread_exit(NULL);
}

void adicionar_na_lista(t_geral **g,t_geral *t,t_geral **u)
{
	if(*g == NULL)
	{
		*g = t;
		*u = *g;
	}
	else
	{
		(*u)->next = t;
		*u = t;
	}
}

void join_threads(t_geral **geral)
{
	t_geral *temp;

	temp = *geral;
	while(temp != NULL)
	{
		pthread_join(temp->mutex->thread,NULL);
		temp = temp->next;
	}
}

void destroy_all_mutex(t_geral **geral)
{
	t_geral *temp;

	temp = *geral;
	while(temp != NULL)
	{
		pthread_mutex_destroy(&(temp->mutex->mutex));
		temp = temp->next;
	}
}

void exit_erro(void)
{
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep\n");
	exit (0);
}

int main(int ac, char **av)
{
	int num;
	int i;
	t_geral *geral;
	t_geral *temp;
	t_geral *ultimo;
	geral = NULL;
	ultimo = NULL;
	if(ac != 5)
		exit_erro();
	num = atoi(av[1]);
	i = 1;
	//isso vai criar as threads e o mutex para cada threads
	while(i <= num)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		temp->mutex->time_to_die = atoi(av[2]);
		temp->mutex->time_to_eat = atoi(av[3]);
		temp->mutex->time_to_sleep = atoi(av[4]);
		temp->mutex->id_philosopher = i;
		iniciar_mutex(temp);
		temp->next = NULL;
		adicionar_na_lista(&geral,temp,&ultimo);
		pthread_create(&(temp->mutex->thread),NULL
			,&teste,temp->mutex);
		i++;
	}
	join_threads(&geral);
	destroy_all_mutex(&geral);
	return 0;
}
