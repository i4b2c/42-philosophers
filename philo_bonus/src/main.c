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
		return ;
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
	while(1)
	{
		printf("%d is eating\n",philo->data->id);
		usleep(philo->data->time_to_eat * 1000);
		printf("%d is sleeping\n",philo->data->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("%d is thinking\n",philo->data->id);
		usleep(philo->data->time_to_think * 1000);
	}
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
		i++;
		philo = philo->next;
		// else
		// 	waitpid(philo->data->pid,NULL,0);
	}
	//waitpid(-1,NULL,0);
}

int main(int ac, char **av)
{
	(void)ac;

	int i;
	pid_t pid;
	t_philo *philo;
	philo = NULL;

	i = 0;
	if(ac != 5)
		return 1;
	while(i < ft_atoi(av[1]))
	{
		init_philo(&philo,av,i);
		i++;
	}
	pid = fork();
	if(pid == (pid_t)0)
		create_philo(philo,ft_atoi(av[1]));
	else
		waitpid(pid,NULL,0);
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
