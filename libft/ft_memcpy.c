/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:45:27 by onaciri           #+#    #+#             */
/*   Updated: 2022/10/21 14:21:25 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == s2)
		return (s1);
	if (!s1 && (!s2 || n == 0))
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(s1 + i) = *(unsigned char *)(s2 + i);
		i++;
	}
	return (s1);
}
