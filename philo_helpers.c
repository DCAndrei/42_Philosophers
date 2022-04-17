/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:27:11 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 23:23:13 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	current_time;
	long			ret;

	gettimeofday(&current_time, NULL);
	ret = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (ret);
}

int	ft_write(long start_time, int id, char *msg)
{
	ft_putnbr_fd(start_time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(id, 1);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	return (0);
}

long	ft_usleep(int duration)
{
	long	start_time;

	start_time = ft_get_time();
	while (ft_get_time() - start_time < duration)
	{
		usleep(USLEEP * 1000);
	}
	return (ft_get_time());
}

int	ft_sleep_time(char *argv[])
{
	int		time_eat;
	int		time_sleep;
	int		time_die;
	int		nb_philo;
	int		ret;

	nb_philo = ft_atoi(argv[1]);
	time_die = ft_atoi(argv[2]);
	time_eat = ft_atoi(argv[3]);
	time_sleep = ft_atoi(argv[4]);
	if (nb_philo % 2 == 0)
		nb_philo /= 2;
	else
		nb_philo = nb_philo / 2 + 1;
	ret = (time_die -(time_eat + time_sleep)) / (10 * nb_philo);
	if (ret <= 0)
		ret = 1;
	return (ret);
}

int	ft_move_position(int position, int size)
{
	if (position == size - 1)
		position = 0;
	else
		position += 1;
	return (position);
}
