/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:11:44 by marvin            #+#    #+#             */
/*   Updated: 2023/07/30 21:11:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void error(void)
{
	write(2,"Error\n",6);
	exit(0);
}

int	ft_atoi(const char *string)
{
	const char	*str;
	int			x;
	int			res;

	x = 1;
	res = 0;
	str = string;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			x *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - 48;
		str++;
	}
	return (res * x);
}

void init_philo(t_philo **philo, char **av,int i)
{
	t_philo *temp;
	t_philo *last_node;

	temp = malloc(sizeof(t_philo));
	temp->next = NULL;
	temp->data = malloc(sizeof(t_data));
	temp->data->id = i+1;
	temp->data->time_to_sleep = ft_atoi(av[2]) -
		(ft_atoi(av[3]) + ft_atoi(av[4]));
	temp->data->time_to_die = ft_atoi(av[2]);
	temp->data->time_to_eat = ft_atoi(av[3]);
	temp->data->time_to_think = ft_atoi(av[4]);

	if(*philo == NULL)
	{
		*philo = temp;
		//return ;
	}
	else
	{
		last_node = *philo;
		while(last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = temp;
	}
}

void philosopher(t_philo *philo)
{
	sem_t *sem;

	sem = sem_open("/my_semaphore",O_RDWR);
	if(sem == SEM_FAILED)
	{
		perror("sem_open");
		return ;
	}
	int i = 0;
	while(i < 10)
	{
		sem_wait(sem);
		sem_wait(sem);
		printf("%d is eating\n",philo->data->id);
		usleep(philo->data->time_to_eat * 1000);
		sem_post(sem);
		sem_post(sem);
		printf("%d is sleeping\n",philo->data->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("%d is thinking\n",philo->data->id);
		usleep(philo->data->time_to_think * 1000);
		i++;
	}
	//exit (0);
}

void create_philo(t_philo *philo, int max_philo)
{
	int i;

	i = 0;
	while(i < max_philo)
	{
		philo->data->pid = fork();
		if(philo->data->pid == (pid_t) 0)
			philosopher(philo);
		philo = philo->next;
		i++;
	}
	free(philo);
	//exit(0);
}

int main(int ac, char **av)
{
	int i;
	pid_t pid;
	t_philo *philo;
	sem_t *sem;

	philo = NULL;
	i = 0;
	if(ac != 5)
		return 1;
	sem_unlink("/my_semaphore");
	sem = sem_open("/my_semaphore", O_CREAT | O_EXCL , 0644 , ft_atoi(av[1]));
	if(sem == SEM_FAILED)
	{
		perror("sem_open");
		return 1;
	}
	pid = fork();
	if(pid == (pid_t)0)
	{
		i = 0;
		while(i < ft_atoi(av[1]))
		{
			init_philo(&philo,av,i);
			i++;
		}
		create_philo(philo,ft_atoi(av[1]));
		exit (0);
	}
	else
	{
		i = 0;
		while(i < ft_atoi(av[1]))
		{
			pid_t pid_check;
			pid_check = waitpid(-1,NULL,WNOHANG);
			if(pid_check > 0)
				i++;
			usleep(1000);
		}
	}
	//funcao para esperar por todos os processos filhos
	// for(i = 0;i < ft_atoi(av[1]);i++)
	// {
	// 	printf("id : %d\n",philo[i].data->id);
	// 	printf("tt think : %d\n",philo[i].data->time_to_think);
	// 	printf("tt eat : %d\n",philo[i].data->time_to_eat);
	// 	printf("tt sleep : %d\n",philo[i].data->time_to_sleep);
	// 	printf("tt die : %d\n\n",philo[i].data->time_to_die);
	// }

	//printf("%d\n",philo[1].data->id);
	return 0;
}
