#include "header.h"

long int calculo(struct timeval time_start, struct timeval time_end)
{
	long int temp;

	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000) -
		(time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return temp;
}

void eat(t_philo *temp)
{
	printf("o philosopho %d esta comendo\n",temp->id);
	usleep(200*1000);
}

void think(t_philo *temp)
{
	printf("o philosopho %d esta pensando\n",temp->id);
	usleep((rand() % 100)*1000);
}

void sleep_p(t_philo *temp)
{
	printf("o philosopho %d esta dormindo\n",temp->id);
	usleep(300*1000);
}

void *philosopher(void *arg)
{
	//static int i;
	//t_geral *temp_geral;
	t_philo *temp;

	temp = (t_philo *)arg;
	//temp = temp_geral[i].philo;
	while(1)
	{
		//come , enquanto n consegue comer pensar ? e depois de comer dorme
		pthread_mutex_lock(&(temp->info->fork));
		pthread_mutex_lock(&(temp->info->next));
		think(temp);
		eat(temp);
		pthread_mutex_unlock(&(temp->info->fork));
		pthread_mutex_unlock(&(temp->info->next));
		sleep_p(temp);
	}
}

void colocar_thread(t_geral *geral, int i)
{
	pthread_t thread;
	pthread_create(&thread,NULL,&philosopher,(void *)geral[i].philo);
	geral[i].philo->thread_id = thread;
}

void colocar_mutex(t_geral *geral, int i)
{
	pthread_mutex_t fork;
	pthread_mutex_t die;
	pthread_mutex_init(&fork,NULL);
	pthread_mutex_init(&die,NULL);
	geral[i].philo->info->fork = fork;
	geral[i].philo->info->die = die;
}

void get_geral_info(t_geral *geral, const int num)
{
	int i;
	pthread_mutex_t add;
	i = 0;

	pthread_mutex_init(&add,NULL);
	while(i < (int)num)
	{
		geral[i].philo = malloc(sizeof(t_philo));
		geral[i].philo->info = malloc(sizeof(t_info));
		if(i)
			geral[i].philo->info->next = geral[i-1].philo->info->fork;
		geral[i].philo->id = i+1;
		geral[i].philo->id_max = num;
		colocar_thread(geral,i);
		colocar_mutex(geral,i);
		i++;
	}
	geral[0].philo->info->next = geral[i-1].philo->info->fork;
}

void printar_teste(t_geral *geral)
{
	int i;
	unsigned int num;

	i = 0;
	num = geral[0].philo->id_max;
	while(i < num)
	{
		printf("valor\t%d\n",geral[i].philo->id);
		i++;
	}
}

void free_geral_info(t_geral *geral)
{
	int i;
	unsigned int num;

	num = geral[0].philo->id_max;
	i = 0;
	while(i < num)
	{
		free(geral[i].philo->info);
		free(geral[i].philo);
		i++;
	}
}

void join_geral_info(t_geral *geral)
{
	int i;
	unsigned int num;

	num = geral[0].philo->id_max;
	i = 0;
	while(i < num)
	{
		pthread_join(geral[i].philo->thread_id,NULL);
		i++;
	}
}

int main(int ac, char **av)
{
    int num_p;

    num_p = atoi(av[1]);
    t_geral *geral;

	srand(time(NULL));
    geral = malloc(sizeof(t_geral) * num_p);
	get_geral_info(geral,num_p);
	join_geral_info(geral);
    free_geral_info(geral);
    free(geral);

    return 0;
}
