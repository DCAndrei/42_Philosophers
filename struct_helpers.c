/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:26:38 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 20:26:33 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_struct_malloc(t_table *table);
static void	ft_partial_philo_init(t_philo *philo, int i);

int	ft_struct_init(t_table *table, char *size)
{
	int		i;

	if (table == NULL)
		return (1);
	table->nb_philo = ft_atoi(size);
	if (ft_struct_malloc(table) == 1)
		return (1);
	if (pthread_mutex_init(&table->general, NULL) != 0)
		return (1);
	table->is_dead = 0;
	table->position = 0;
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->mutex[i], NULL) != 0)
			return (1);
		table->is_taken[i] = -1;
		table->eat[i] = -1;
		table->status[i] = 0;
		table->start_time[i] = -1;
		table->init_time[i] = -1;
		i += 1;
	}
	return (0);
}

static int	ft_struct_malloc(t_table *table)
{
	table->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* table->nb_philo);
	if (table->mutex == NULL)
		return (1);
	table->thread = (pthread_t *)malloc(sizeof(pthread_t) * table->nb_philo);
	if (table->thread == NULL)
		return (1);
	table->eat = (int *)malloc(sizeof(int) * table->nb_philo);
	if (table->eat == NULL)
		return (1);
	table->is_taken = (int *)malloc(sizeof(int) * table->nb_philo);
	if (table->is_taken == NULL)
		return (1);
	table->status = (int *)malloc(sizeof(int) * table->nb_philo);
	if (table->status == NULL)
		return (1);
	table->start_time = (long *)malloc(sizeof(long) * table->nb_philo);
	if (table->start_time == NULL)
		return (1);
	table->init_time = (long *)malloc(sizeof(long) * table->nb_philo);
	if (table->init_time == NULL)
		return (1);
	if (ft_create_waiting_list(&table->waiting_list, table->nb_philo) == 1)
		return (1);
	return (0);
}

int	ft_free_structure(t_table *table)
{
	int		i;
	int		ret;

	ret = 0;
	if (pthread_mutex_destroy(&table->general) != 0)
		ret = 1;
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_destroy(&table->mutex[i]) != 0)
			ret = 1;
		i += 1;
	}
	free (table->waiting_list);
	free (table->thread);
	free (table->mutex);
	free (table->eat);
	free (table->is_taken);
	free (table->start_time);
	free (table->status);
	free (table->init_time);
	return (ret);
}

t_philo	*ft_create_philos(t_table *table, int argc, char *argv[])
{
	int			i;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * table->nb_philo);
	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		ft_partial_philo_init(&philo[i], i);
		philo[i].table = table;
		philo[i].time_die = ft_atoi(argv[2]);
		philo[i].time_eat = ft_atoi(argv[3]);
		philo[i].time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].eat_times = ft_atoi(argv[5]);
		table->eat[i] = philo[i].eat_times;
		if (philo[i].prev == -1)
			philo[i].prev = table->nb_philo - 1;
		philo[i].start_time = ft_get_time();
		philo[i].last_meal = ft_get_time();
		i += 1;
	}
	return (philo);
}

static void	ft_partial_philo_init(t_philo *philo, int i)
{
		philo->id = i;
		philo->prev = i - 1;
		philo->status = 0;
		philo->prev_fork = -1;
		philo->own_fork = -1;
		philo->eat_times = -1;
		philo->is_dead = 0;
}
