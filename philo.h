/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:08:07 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 23:29:57 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define MICROSLEEP 100
# define USLEEP 2

typedef struct s_table
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	int				*is_taken;
	pthread_mutex_t	general;
	long			*start_time;
	long			*init_time;
	int				*eat;
	int				*status;
	int				is_dead;
	int				nb_philo;
	int				*waiting_list;
	int				position;
}				t_table;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	int				prev;
	int				status;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_times;
	int				is_dead;
	long			start_time;
	long			last_meal;
	int				prev_fork;
	int				own_fork;
}				t_philo;

//libft_helpers.c

int		ft_atoi(char const *nptr);
int		ft_strlen(char *str);
void	ft_putnbr_fd(long n, int fd);

//struct_helpers.c

int		ft_struct_init(t_table *table, char *size);
int		ft_free_structure(t_table *table);
t_philo	*ft_create_philos(t_table *table, int argc, char *argv[]);

//struct_helpers_2.c

int		ft_create_waiting_list(int **meal_list, int size);

//philo_helpers.c

long	ft_get_time(void);
int		ft_write(long start_time, int id, char *msg);
long	ft_usleep(int duration);
int		ft_sleep_time(char *argv[]);
int		ft_move_position(int position, int size);

//thread_helpers.c

void	*ft_routine(void *data);
void	ft_take_left_fork(t_philo *philo, int id, int prev, long start);
void	ft_take_right_fork(t_philo *philo, int id, int prev, long start);
long	ft_philo_sleep(t_philo *philo, int id, int prev, long start);
long	ft_philo_think(t_philo *philo, int id, int prev, long start);

//thread_helpers_2.c

void	ft_philo_cycle(t_philo *philo, int id, int prev, long start);

//main_helpers.c

void	ft_print_input_error(void);
int		ft_check_input(int argc, char *argv[]);
int		ft_check_int(char *str);
int		ft_check_and_init(t_table *table, t_philo **philo, \
		int argc, char *argv[]);

#endif