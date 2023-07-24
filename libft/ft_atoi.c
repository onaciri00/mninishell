/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:37:19 by onaciri           #+#    #+#             */
/*   Updated: 2022/11/05 11:39:02 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static unsigned long	ft_(unsigned long res, const char *str, int i, int f)
{
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		if (f == -1 && res > 9223372036854775807)
			return (0);
		else if (res >= 9223372036854775807)
			return (-1);
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				f;

	i = 0;
	res = 0;
	f = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		if (str[i] == '-')
			f *= -1;
		i++;
	}
	res = ft_(res, str, i, f);
	return ((int)res * f);
}
