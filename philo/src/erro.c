/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:38:18 by marvin            #+#    #+#             */
/*   Updated: 2023/05/12 13:38:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int	only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_error(char **av, int ac)
{
	int	ret;

	ret = 0;
	if (ac == 6 && !only_digit(av[5]))
		ret = 1;
	if (!only_digit(av[4]) || !only_digit(av[3])
		|| !only_digit(av[2]) || !only_digit(av[1]))
		ret = 1;
	if (ft_atoi(av[4]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[2]) <= 0 || ft_atoi(av[1]) <= 0)
		ret = 1;
	return (ret);
}
