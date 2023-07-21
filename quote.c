/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:16:40 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/21 13:34:08 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	perfect_cmd(char *str)
{
	char	*cp;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
		if(str[i] != 127)
			size++;
	cp = malloc(sizeof(char) * size + 1);
	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] != 127)
		{
			cp[size] = str[i];
			size++;
		}
	}
	cp[size] = '\0';
	size = -1;
	while (cp[++size])
		str[size] = cp[size];
	str[size] = '\0';
	free(cp);
}


void    deqou_cmd(char *str, int i)
{
	char	quote;

	while (str[++i])
	{
		if (is_quote(str, i))
		{
			quote = str[i];
			str[i] = 127;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] && str[i] == quote)
			{
				str[i] = 127;
			}
		}
	}
	perfect_cmd(str);
}

int	is_quote(char *str, int i)
{
	int	j;
	int	sqo;
	int	dqo;

	j = 0;
	sqo = 0;
	dqo =0;
	while (str[j] && i >= j)
	{
		if (str[j] == '"' && !sqo)
			dqo++;
		if (str[j] == '\'' && !dqo)
			sqo++;
		if (sqo == 2 || dqo == 2)
		{
			sqo = 0;
			dqo = 0;
		}
		j++;
	}
	if (dqo == 1)
		return (2);
	else if (sqo == 1)
		return (1);
	return (0);
}