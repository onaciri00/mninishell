/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:41:44 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/14 07:36:01 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	b;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	j = ft_strlen(s1);
	j = j + ft_strlen(s2);
	i = 0;
	b = 0;
	if (!s1[0] && !s2[0])
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * j + 1);
	if (!str)
		return (0);
	while (i <= j && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (i <= j && s2[b] != '\0')
		str[i++] = s2[b++];
	str[i] = '\0';
	return (free(s1), free(s2), str);
}
