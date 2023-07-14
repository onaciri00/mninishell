/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:16:40 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/14 14:38:55 by onaciri          ###   ########.fr       */
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


void    deqou_cmd(char *str, int sqo, int dqo, int i)
{
	char	quote;

	//add expand
	while (str[++i])
	{
		if (str[i] == '"' && !sqo)
			dqo++;
		else if (str[i] == '\'' && !dqo)
			sqo++;
		if (sqo || dqo)
		{
			quote = str[i];
			str[i] = 127;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] && str[i] == quote)
			{
				str[i] = 127;
				dqo = 0;
				sqo = 0;
			}
		}
	}
	perfect_cmd(str);
}