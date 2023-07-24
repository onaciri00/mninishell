/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:16:43 by onaciri           #+#    #+#             */
/*   Updated: 2022/10/24 17:24:04 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*mal;

	if (size && count >= SIZE_MAX / size)
		return (0);
	mal = malloc(count * size);
	if (!mal)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		*(unsigned char *)(mal + i) = 0;
		i++;
	}
	return (mal);
}
