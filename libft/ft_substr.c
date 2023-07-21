/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:21:51 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/21 08:27:49 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	j;

	j = 0;
	i = start;
	if (!str)
		return (NULL);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	if (ft_strlen(str) - start <= len)
		len = ft_strlen(&str[start]);
	if (str[0] == '\0' || start >= ft_strlen(str) || !len)
		return (ft_strdup(""));
	subs = malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	while (str[i] != '\0' && j < len)
	{
		subs[j] = str[i];
		i++;
		j++;
	}
	subs[j] = '\0';
	return (subs);
}
