#include "header.h"

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

int main(void)
{
	int i;
	t_mutex mutex1;
	t_mutex mutex2;
	pthread_mutex_t mutex;
	pthread_t t1;
	pthread_t t2;

	i = 0;
	pthread_mutex_init(&mutex,NULL);
	//mutex1.num = &i;
	//mutex1.mutex = &mutex;
	//mutex2.num = &i;
	//mutex2.mutex = &mutex;
	iniciar_mutex(&mutex1,&i,&mutex);
	iniciar_mutex(&mutex2,&i,&mutex);
	pthread_create(&t1,NULL,&teste,(void *) &mutex1);
	pthread_create(&t2,NULL,&teste,(void *) &mutex2);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&mutex);
	printf("valor final:%d\n",i);
	return 0;
}
