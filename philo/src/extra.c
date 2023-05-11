/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:04:28 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 05:04:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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

void	print_fork(struct timeval time_start, t_mutex *temp)
{
	pthread_mutex_lock((temp->print));
	if (!temp->end)
		print_action(get_p_time(time_start), temp->id_philosopher, 3);
	pthread_mutex_unlock((temp->print));
}

void	print_action(long num, int philo, int op)
{
	const char	*options[5] = {
		"is sleeping",
		"is eating",
		"is thiking",
		"has taken a fork",
		"is dead"
	};

	printf("%ld\t %d %s\n", num, philo, options[op]);
}
