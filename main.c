/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:25:56 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 22:55:55 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_threads(t_table *table, int argc, char *argv[]);
static int	ft_check_philo(t_table *table, int *eat, char *argv[]);

int	main(int argc, char *argv[])
{
	int		i;
	t_table	table;
	t_philo	*philo;

	philo = NULL;
	if (ft_check_and_init(&table, &philo, argc, argv) == 1)
		return (1);
	i = 0;
	while (i++ < table.nb_philo)
		pthread_create(&table.thread[i - 1], NULL, ft_routine, &philo[i - 1]);
	ft_check_threads(&table, argc, argv);
	i = 0;
	while (i++ < table.nb_philo)
		pthread_join(table.thread[i - 1], NULL);
	free (philo);
	if (ft_free_structure(&table) == 1)
		return (1);
	return (0);
}

static int	ft_check_threads(t_table *table, int argc, char *argv[])
{
	int		rep;
	int		eat;

	rep = 1;
	while (rep == 1)
	{
		eat = 0;
		rep = ft_check_philo(table, &eat, argv);
		if (argc == 6 && rep == 1 && eat == 0)
			break ;
		usleep(5 * 1000);
	}
	return (0);
}

static int	ft_check_philo(t_table *table, int *eat, char *argv[])
{
	int		i;
	long	tt;

	i = 0;
	pthread_mutex_lock(&table->general);
	while (i < table->nb_philo && table->is_dead == 0)
	{
		tt = ft_get_time();
		if (tt - table->start_time[i] > ft_atoi(argv[2]) && table->eat[i] != 0 \
			&& (table->status[i] != 1 || table->nb_philo == 1) && \
			table->start_time[i] != -1)
		{
			ft_write(tt - table->init_time[i], i + 1, "died");
			table->is_dead = 1;
			pthread_mutex_unlock(&table->general);
			return (0);
		}
		if (table->eat[i] != 0)
				*eat = 1;
		i += 1;
	}
	pthread_mutex_unlock(&table->general);
	return (1);
}
