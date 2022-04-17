/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:24:27 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 20:27:13 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check_size(int *size, int *t);

int	ft_create_waiting_list(int **meal_list, int size)
{
	int		i;
	int		t;

	*meal_list = (int *)malloc(sizeof(int) * size);
	if (*meal_list == NULL)
		return (1);
	t = 0;
	ft_check_size(&size, &t);
	i = 0;
	while (i < size)
	{
		if (i * 2 < size)
			(*meal_list)[i] = i * 2;
		else
			(*meal_list)[i] = i * 2 - (size - 1);
		i += 1;
	}
	if (t == 1)
	{
		size += 1;
		(*meal_list)[size - 1] = size - 1;
	}
	return (0);
}

static void	ft_check_size(int *size, int *t)
{
	if (*size % 2 != 0)
	{
		*size -= 1;
		*t = 1;
	}
}
