/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:25:01 by acretu            #+#    #+#             */
/*   Updated: 2022/04/15 00:20:38 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_error(void);

void	ft_print_input_error(void)
{
	printf("Error: Wrong arguments\n");
	printf("Expected: ./philo <n_p> <t_d> <t_e> <t_s> [<n_e_e>]\n");
	printf("\nusage:\n");
	printf("n_p - number of philosophers, positive int\n");
	printf("t_d - time to die, in milliseconds, positive int\n");
	printf("t_e - time to eat, in milliseconds, positive int\n");
	printf("t_s - time to sleep, in milliseconds, positive int\n");
	printf("n_e_e - OPTIONAL argument, number of times each philosopher must \
eat\n");
	printf("If not specified, the simulation stops when a philo dies\n");
	printf("If specified the simulation stops when all philo have eaten at \
least n_e_e times.\n\n");
}

int	ft_check_input(int argc, char *argv[])
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	printf("Input checking:\n");
	while (++i < argc)
	{
		if (ft_check_int(argv[i]) == 1)
		{
			printf("Wrong input, expected a positive int: %s\n", argv[i]);
			ret = 1;
		}
		else
			printf("Correct input: %s\n", argv[i]);
	}
	if (ret == 1)
		ft_print_error();
	return (ret);
}

static void	ft_print_error(void)
{
	printf("\nusage:\n");
	printf("n_p - number of philosophers, positive int\n");
	printf("t_d - time to die, in milliseconds, positive int\n");
	printf("t_e - time to eat, in milliseconds, positive int\n");
	printf("t_s - time to sleep, in milliseconds, positive int\n");
	printf("n_e_e - OPTIONAL argument, number of times each philosopher must \
eat, positive int\n");
}

int	ft_check_int(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '0')
		return (1);
	while ((str[i] >= 9 && str[i] < 14) || str[i] == ' ')
		i += 1;
	if (str[i] == '-' || str[i] == '0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i += 1;
	}
	return (0);
}

int	ft_check_and_init(t_table *table, t_philo **philo, int argc, char *argv[])
{
	int		i;

	if (argc != 5 && argc != 6)
	{
		ft_print_input_error();
		return (1);
	}
	if (ft_check_input(argc, argv) == 1)
		return (1);
	if (ft_struct_init(table, argv[1]) == 1)
		return (1);
	*philo = ft_create_philos(table, argc, argv);
	if (philo == NULL)
		return (1);
	(*philo)[0].start_time = ft_get_time();
	i = 1;
	while (i < table->nb_philo)
	{
		(*philo)[i].start_time = (*philo)[0].start_time;
		i += 1;
	}
	return (0);
}
