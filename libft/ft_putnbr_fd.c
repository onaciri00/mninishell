/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:54:37 by onaciri           #+#    #+#             */
/*   Updated: 2022/10/24 20:52:38 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	write_num(int j, int n, int fd, int i)
{
	while (i > 1)
	{
		j *= 10;
		i--;
	}
	while (j >= 1)
	{
		ft_putchar_fd((n / j) + 48, fd);
		n %= j;
		j /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 1;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	count = n;
	while (count >= 1)
	{
		count = count / 10;
		i++;
	}
	write_num(j, n, fd, i);
}
