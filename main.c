#include "header.h"

void morreu_philosopher(t_mutex *temp);

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

void pensar(t_mutex *temp,struct timeval time_start)
{
	long int num_temp;
	struct timeval time_end;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld the %d is thinking\n"
		,num_temp,temp->id_philosopher);
	//rand esta apenas para eu tester uma coisa
	usleep(rand () % 400*1000);
}

void comer(t_mutex *temp,t_mutex *mutex
	,struct timeval time_start)
{
	long int num_temp;
	long int i;
	struct timeval time_end;
	struct timeval teste1;
	struct timeval teste3;

	gettimeofday(&teste1,NULL);
	num_temp = calculo(time_start,time_end);
	pthread_mutex_lock(&(temp->mutex));
	pthread_mutex_lock(&(mutex->mutex));
	gettimeofday(&teste3,NULL);
	i = calculo(teste1,teste3);
	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	if(i)
	{
		printf("%ld %d is thinking\n"
			,num_temp,temp->id_philosopher);
		usleep(i*1000);
		temp->time_to_die -= i;
		//if(check_morte(temp->time_to_die,num_temp));
		//	morreu_philosopher(temp);
	}
	if(temp->time_to_die < 0)
		morreu_philosopher(temp);
	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld %d is eating\n"
		,num_temp,temp->id_philosopher);
	//temp->time_to_die -= temp->time_to_sleep;
	temp->time_to_die += temp->time_to_eat;
	usleep(temp->time_to_eat*1000);
	pthread_mutex_unlock(&(temp->mutex));
	pthread_mutex_unlock(&(mutex->mutex));
	if(temp->time_to_die <= 0)
		morreu_philosopher(temp);
}

void dormir(t_mutex *temp,struct timeval time_start)
{
	int long num_temp;
	struct timeval time_end;

	gettimeofday(&time_end,NULL);
	num_temp = calculo(time_start,time_end);
	printf("%ld %d is sleeping\n"
		,num_temp,temp->id_philosopher);
	temp->time_to_die -= temp->time_to_sleep;
	//rand esta apenas para eu tester uma coisa
	usleep(temp->time_to_sleep*1000);
	if(temp->time_to_die < 0)
		morreu_philosopher(temp);
}

void morreu_philosopher(t_mutex *temp)
{
	printf("%d is died\n",temp->id_philosopher);
	pthread_exit(NULL);
	exit (0);
}

void *teste(void *arg)
{
	int i;
	struct timeval time_start;
	long int num;
	pthread_mutex_t *mutex_next;
	t_geral *temp;

	i = 0;
	temp = (t_geral *)arg;
	gettimeofday(&time_start,NULL);
	while(1)
	{
		if(temp->mutex->time_to_die <= 0)
			morreu_philosopher(temp->mutex);
		//pensar(temp->mutex,time_start);
		if(temp->mutex->id_philosopher < temp->mutex->max)
			comer(temp->mutex
			,temp->next->mutex,time_start);
		else
			comer(temp->mutex,
				temp->mutex->first_mutex,time_start);
		dormir(temp->mutex,time_start);
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

void create_lista(t_geral **geral, int num,char **av)
{
	int i;
	t_geral *temp;
	t_geral *ultimo;
	t_mutex *mutex;

	ultimo = NULL;
	i = 1;
	while(i <= num)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		temp->mutex->max = atoi(av[1]);
		temp->mutex->time_to_die = atoi(av[2]);
		temp->mutex->time_to_die_reset = atoi(av[2]);
		temp->mutex->time_to_eat = atoi(av[3]);
		temp->mutex->time_to_sleep = atoi(av[4]);
		temp->mutex->id_philosopher = i;
		iniciar_mutex(temp);
		if(i == 1)
			mutex = temp->mutex;
		temp->mutex->first_mutex = mutex;
		temp->next = NULL;
		adicionar_na_lista(geral,temp,&ultimo);
		//pthread_create(&(temp->mutex->thread),NULL
		//	,&teste,temp->mutex);
		i++;
	}
}

void create_threads(t_geral **geral)
{
	t_geral *temp_geral;

	temp_geral = *geral;
	while(temp_geral != NULL)
	{
		pthread_create(&(temp_geral->mutex->thread),NULL
			,&teste,temp_geral);
		temp_geral = temp_geral->next;
	}
}

int main(int ac, char **av)
{
	int num;
	t_geral *geral;
	//apenas para testar
	srand(time(NULL));

	geral = NULL;
	if(ac != 5)
		exit_erro();
	num = atoi(av[1]);
	create_lista(&geral,num,av);
	create_threads(&geral);
	join_threads(&geral);
	destroy_all_mutex(&geral);
	return 0;
}
