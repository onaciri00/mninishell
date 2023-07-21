/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:44:51 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/14 10:36:36 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	check_in(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count + 1);
}

static void	*free_split(char **split, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
static int	ft_len(size_t i, const char *s, char c)
{
	int	len;
	int	sqo;
	int	dqo;

	sqo = 0;
	len = 0;
	dqo = 0;
	while (s[i])
	{
		if (s[i] == '"' && !sqo)
			dqo++;
		else if (s[i] == '\'' && !dqo)
			sqo++;
		if (dqo == 2)
			dqo = 0;
		if (sqo == 2)
			sqo = 0;
		if (s[i] == c && !sqo && !dqo)
			break;
		i++;
		len++;
	}
	return (len);
}
static char	**full_str(const char *s, char c, char **str, size_t i)
{
	size_t	j;
	size_t	len;

	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len = ft_len(i, s, c);
			i += len;
			str[j] = ft_substr((char *)(s +(i - len)), 0, len);
			if (!str[j])
				return (free_split(str, j));
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	j = 0;
	if (!s)
		return (0);
	i = 0;
	str = malloc(sizeof(char *) * (check_in(s, c) + 1));
	if (!str)
		return (0);
	return (full_str(s, c, str, j));
}
