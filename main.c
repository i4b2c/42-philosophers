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

	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000) -
    		(time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return temp;
}

void pensar(t_mutex *temp,struct timeval time_start,struct timeval time_end)
{
	long int num_temp;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld the %d is thinking\n"
		,num_temp,temp->id_philosopher);
	usleep(rand() % 400*1000);
}

void comer(t_mutex *temp,struct timeval time_start,struct timeval time_end)
{
	long int num_temp;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(&(temp->mutex));
	printf("%ld the %d is eating\n"
		,num_temp,temp->id_philosopher);
	temp->time_to_die = temp->time_to_die_reset;
	pthread_mutex_unlock(&(temp->mutex));
	usleep(rand() % temp->time_to_eat*1000);
}

void dormir(t_mutex *temp,struct timeval time_start,struct timeval time_end)
{
	int long num_temp;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld the %d is sleeping\n"
		,num_temp,temp->id_philosopher);
	temp->time_to_die -= temp->time_to_sleep;
	usleep(rand() % temp->time_to_sleep*1000);
}

void morreu_philosopher(t_mutex *temp)
{
	printf("the %d is died\n",temp->id_philosopher);
	pthread_exit(NULL);
	exit (0);
}

void *teste(void *arg)
{
	int i;
	struct timeval time_start;
	struct timeval time_end;
	long int num;
	t_mutex *temp;

	i = 0;
	temp = (t_mutex *)arg;
	usleep(10);
	gettimeofday(&time_start,NULL);
	gettimeofday(&time_end,NULL);
	while(1)
	{
		pensar(temp,time_start,time_end);
		comer(temp,time_start,time_end);
		dormir(temp,time_start,time_end);
		if(temp->time_to_die <= 0)
			morreu_philosopher(temp);
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

void create_threads(t_geral **geral, int num,char **av)
{
	int i;
	t_geral *temp;
	t_geral *ultimo;

	ultimo = NULL;
	i = 1;
	while(i <= num)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		temp->mutex->time_to_die = atoi(av[2]);
		temp->mutex->time_to_die_reset = atoi(av[2]);
		temp->mutex->time_to_eat = atoi(av[3]);
		temp->mutex->time_to_sleep = atoi(av[4]);
		temp->mutex->id_philosopher = i;
		iniciar_mutex(temp);
		temp->next = NULL;
		adicionar_na_lista(geral,temp,&ultimo);
		pthread_create(&(temp->mutex->thread),NULL
			,&teste,temp->mutex);
		i++;
	}
}

int main(int ac, char **av)
{
	int num;
	t_geral *geral;

	srand(time(NULL));
	geral = NULL;
	if(ac != 5)
		exit_erro();
	num = atoi(av[1]);
	create_threads(&geral,num,av);
	join_threads(&geral);
	destroy_all_mutex(&geral);
	return 0;
}
