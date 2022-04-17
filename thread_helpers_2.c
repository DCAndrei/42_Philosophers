/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 23:24:53 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 23:32:51 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_cycle(t_philo *philo, int id, int prev, long start)
{
	long	time_error;

	time_error = 0;
	while (philo->eat_times != 0 && philo->is_dead == 0)
	{
		ft_take_left_fork(philo, id, prev, start);
		ft_take_right_fork(philo, id, prev, start);
		time_error += ft_philo_sleep(philo, id, prev, start);
		time_error += ft_philo_think(philo, id, prev, start);
		if (prev == id)
			return ;
		pthread_mutex_lock(&philo->table->general);
		if (philo->table->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->table->general);
			return ;
		}
		philo->table->start_time[id] += time_error;
		start += time_error;
		time_error = 0;
		pthread_mutex_unlock(&philo->table->general);
	}
}
