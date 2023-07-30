/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:43:59 by onaciri           #+#    #+#             */
/*   Updated: 2022/10/22 10:09:00 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*src;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	src = (char *) malloc((i + 1) * sizeof(char));
	if (!src)
		return (0);
	while (s1[j] != '\0')
	{
		src[j] = s1[j];
		j++;
	}
	src[j] = '\0';
	return (src);
}
