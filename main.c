#include "header.h"

void iniciar_mutex(t_mutex *temp, pthread_mutex_t *mutex)
{
	temp->mutex = mutex;
}

void *teste(void *arg)
{
	int i;
	int *pensar;
	int *dormir;
	int philosophe;
	t_mutex *temp;
	pthread_mutex_t *mutex;

	temp = (t_mutex *)arg;
	i = 0;
	mutex = temp->mutex;
	pensar = temp->pensar;
	dormir = temp->dormir;
	philosophe = temp->philosopher;
	if(dormir < pensar)
	{	
		while(1)
		{
			//pthread_mutex_lock(mutex);
			printf("philosopho %d esta a dormir\n"
				,philosophe);
			usleep(*dormir);
			//pthread_mutex_unlock(mutex);
		}
	}
	else
	{
		while(1)
		{
			//pthread_mutex_lock(mutex);
			printf("philosopho %d esta a pensar\n"
				,philosophe);
			usleep(*pensar);
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

int main(int ac, char **av)
{
	int num;
	int i;
	pthread_mutex_t mutex;
	t_geral *geral;
	t_geral *temp;
	t_geral *ultimo;
	int dormir;
	int pensar;
	int morte;
	geral = NULL;
	ultimo = NULL;

	if(ac != 5)
		return 0;
	num = atoi(av[1]);
	dormir = atoi(av[2]);
	pensar = atoi(av[3]);
	morte = atoi(av[4]);
	pthread_mutex_init(&mutex,NULL);
	i = 1;
	//isso vai criar as threads e o mutex para cada threads
	while(num > 0)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		temp->mutex->dormir = &dormir;
		temp->mutex->pensar = &pensar;
		temp->mutex->morte = morte;
		temp->mutex->philosopher = i;
		iniciar_mutex(temp->mutex,&mutex);
		temp->next = NULL;
		adicionar_na_lista(&geral,temp,&ultimo);
		pthread_create(&(temp->mutex->thread),NULL
			,&teste,temp->mutex);
		i++;
		num--;

	}
	ultimo = geral;
	//vai dar join em cada thread
	while(ultimo != NULL)
	{
		pthread_join(ultimo->mutex->thread,NULL);
		ultimo = ultimo->next;
	}
	//destruir o mutex que eu criei
	pthread_mutex_destroy(&mutex);
	return 0;
}
