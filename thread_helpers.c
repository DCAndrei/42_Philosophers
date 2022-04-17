/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:27:25 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 23:39:21 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//philo status 0 Thinking, 1 Eating, 2 Sleeping

#include "philo.h"

void	*ft_routine(void *data)
{
	t_philo		*philo;
	int			id;
	int			prev;
	long		start;

	philo = (t_philo *)data;
	id = philo->id;
	prev = philo->prev;
	pthread_mutex_lock(&philo->table->general);
	philo->table->start_time[id] = ft_get_time();
	philo->table->init_time[id] = ft_get_time();
	start = ft_get_time();
	if (philo->table->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->table->general);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->general);
	ft_philo_cycle(philo, id, prev, start);
	return (0);
}

void	ft_take_left_fork(t_philo *philo, int id, int prev, long start)
{
	if (philo->prev_fork == -1 && philo->status == 0)
	{
		pthread_mutex_lock(&philo->table->general);
		if (philo->table->status[id] == 0 && philo->table->is_taken[prev] == -1 \
		&& philo->table->waiting_list[philo->table->position] == id)
		{
			pthread_mutex_lock(&philo->table->mutex[prev]);
			philo->table->is_taken[prev] = id;
			pthread_mutex_unlock(&philo->table->mutex[prev]);
			philo->prev_fork = id;
			if (philo->table->is_dead == 0)
				ft_write(ft_get_time() - start, id + 1, "has taken a fork");
		}
		pthread_mutex_unlock(&philo->table->general);
	}
	else
		usleep(MICROSLEEP);
}

void	ft_take_right_fork(t_philo *philo, int id, int prev, long start)
{
	if (philo->prev_fork == id && philo->own_fork == -1 && philo->status == 0)
	{
		pthread_mutex_lock(&philo->table->general);
		if (philo->table->status[id] == 0 && philo->table->is_taken[prev] == id)
		{
			pthread_mutex_lock(&philo->table->mutex[id]);
			philo->table->is_taken[id] = id;
			pthread_mutex_unlock(&philo->table->mutex[id]);
			philo->table->position = ft_move_position(philo->table->position, \
			philo->table->nb_philo);
			philo->table->status[id] = 1;
			philo->status = 1;
			philo->table->eat[id] -= 1;
			philo->eat_times -= 1;
			philo->own_fork = id;
			if (philo->table->is_dead == 0)
				ft_write(ft_get_time() - start, id + 1, "has taken a fork");
			if (philo->table->is_dead == 0)
				ft_write(ft_get_time() - start, id + 1, "is eating");
			philo->table->start_time[id] = ft_get_time();
		}
		pthread_mutex_unlock(&philo->table->general);
	}
	else
		usleep(MICROSLEEP);
}

long	ft_philo_sleep(t_philo *philo, int id, int prev, long start)
{
	long	time_error;
	long	tt;

	time_error = 0;
	if (philo->status == 1 && prev != id)
	{
		tt = ft_usleep(philo->time_eat);
		pthread_mutex_lock(&philo->table->general);
		philo->table->is_taken[prev] = -1;
		philo->table->is_taken[id] = -1;
		philo->table->status[id] = 2;
		philo->status = 2;
		philo->prev_fork = -1;
		philo->own_fork = -1;
		time_error = ft_get_time() - tt;
		if (philo->table->is_dead == 0)
			ft_write(ft_get_time() - start, id + 1, "is sleeping");
		pthread_mutex_unlock(&philo->table->general);
	}
	else
		usleep(MICROSLEEP);
	return (time_error);
}

long	ft_philo_think(t_philo *philo, int id, int prev, long start)
{
	long	time_error;
	long	tt;

	time_error = 0;
	if (philo->status == 2 && prev != id)
	{
		tt = ft_usleep(philo->time_sleep);
		pthread_mutex_lock(&philo->table->general);
		philo->table->status[id] = 0;
		philo->status = 0;
		time_error = ft_get_time() - tt;
		if (philo->table->is_dead == 0)
			ft_write(ft_get_time() - start, id + 1, "is thinking");
		pthread_mutex_unlock(&philo->table->general);
	}
	else
		usleep(MICROSLEEP);
	return (time_error);
}
