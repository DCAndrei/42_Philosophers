/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:29:51 by acretu            #+#    #+#             */
/*   Updated: 2022/04/14 23:06:16 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_number(char const *nptr, int sign);

int	ft_atoi(char const *nptr)
{
	int		sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	return ((int)ft_number(nptr, sign));
}

static long	ft_number(char const *nptr, int sign)
{
	long		nb;
	int			digits;

	digits = 0;
	nb = 0;
	while ((*nptr) >= '0' && (*nptr) <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
		digits++;
	}
	if (digits > 19 && sign == 1)
		return (-1);
	else if (digits > 19)
		return (0);
	return (nb * sign);
}

int	ft_strlen(char *str)
{
	int		len;

	if (str == NULL)
		return (-1);
	len = 0;
	while (str[len] != '\0')
		len += 1;
	return (len);
}

static void	print_poz_nbr(long n, int fd);

void	ft_putnbr_fd(long n, int fd)
{
	char		c;
	long		i;

	if (n == 0)
	{
		c = '0';
		write(fd, &c, 1);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		i = n % 10;
		if (i < 0)
			i = -i;
		c = '0' + i;
		n = n / 10;
		n = -n;
		print_poz_nbr(n, fd);
		write(fd, &c, 1);
	}
	else
		print_poz_nbr(n, fd);
}

static	void	print_poz_nbr(long n, int fd)
{
	char		c;

	if (n == 0)
		return ;
	print_poz_nbr(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
}
