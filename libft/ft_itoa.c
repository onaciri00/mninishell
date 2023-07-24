/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:06:48 by onaciri           #+#    #+#             */
/*   Updated: 2022/11/05 12:06:54 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*full_str(char *str, int count, int n, long j)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		str[i] = '-';
		i++;
		count++;
	}
	while (i < count)
	{
		str[i] = (char)(n / j) + 48;
		i++;
		n %= j;
		j /= 10;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_count(int num)
{
	int	count;

	count = 1;
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while (num > 9)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			count;
	int			z;
	long		j;

	j = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_count(n);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (0);
	z = 0;
	while (count - 1 > z)
	{
		j = j * 10;
		z++;
	}
	if (n < 0)
	{
		j /= 10;
		count--;
	}
	str = full_str(str, count, n, j);
	return (str);
}
