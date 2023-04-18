#include "header.h"

typedef struct d_geral
{
	t_mutex *mutex;
	struct d_geral *next;
}	t_geral;

void iniciar_mutex(t_mutex *temp, int *num, pthread_mutex_t *mutex)
{
	temp->num = num;
	temp->mutex = mutex;
}

void *teste(void *arg)
{
	int i;
	t_mutex *temp;
	int *num;
	pthread_mutex_t *mutex;

	temp = (t_mutex *)arg;
	i = 0;
	num = temp->num;
	mutex = temp->mutex;
	while(i < 1000000)
	{
		pthread_mutex_lock(mutex);
		i++;
		(*num)++;
		pthread_mutex_unlock(mutex);
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
	geral = NULL;
	ultimo = NULL;

	if(ac == 1)
		return 0;
	i = 0;
	num = atoi(av[1]);
	pthread_mutex_init(&mutex,NULL);
	while(num > 0)
	{
		temp = malloc(sizeof(t_geral));
		temp->mutex = malloc(sizeof(t_mutex));
		iniciar_mutex(temp->mutex,&i,&mutex);
		temp->next = NULL;
		adicionar_na_lista(&geral,temp,&ultimo);
		/*if (geral == NULL) {
            geral = temp;
            ultimo = geral;
        } else {
            ultimo->next = temp;
            ultimo = temp;
        }*/
		pthread_create(&(temp->mutex->thread),NULL
			,&teste,temp->mutex);
		num--;

	}
	num = atoi(av[1]);
	ultimo = geral;
	while(ultimo != NULL)
	{
		pthread_join(ultimo->mutex->thread,NULL);
		ultimo = ultimo->next;
	}
	pthread_mutex_destroy(&mutex);
	printf("valor final:%d\n",i);
	return 0;
}
