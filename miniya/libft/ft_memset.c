/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:35:12 by onaciri           #+#    #+#             */
/*   Updated: 2022/10/21 09:53:12 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*cp;

	i = 0;
	cp = (unsigned char *)str;
	while (n > i)
	{
		cp[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
