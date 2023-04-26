/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:25:09 by marvin            #+#    #+#             */
/*   Updated: 2023/04/26 03:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int	calculo(struct timeval time_start, struct timeval time_end)
{
	long int	temp;

	temp = ((time_end.tv_sec * 1000 + time_end.tv_usec / 1000)
			- (time_start.tv_sec * 1000 + time_start.tv_usec / 1000));
	return (temp);
}
