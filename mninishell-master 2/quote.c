/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:16:40 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/24 07:37:28 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	lim_state(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

void	rem_quote(t_lexer *cmd)
{
	t_file	*file;
	int		i;

	file = cmd->file;
	i = -1;
	while (cmd->cmd[++i])
		deqou_cmd(cmd->cmd[i], 0, 0, 0);
	while (file)
	{
		if (file->file)
			deqou_cmd(file->file, 0, 0, 0);
		else if (file->limeter)
		{
			if (lim_state(file->limeter))
				file->lim_con = 1;
			else
				file->lim_con = 0;
			deqou_cmd(file->limeter, 0, 0, 0);
		}
		file = file->next;
	}
}

void	perfect_cmd(char *str)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != 127)
		{
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
}


void    deqou_cmd(char *str, int sqo, int dqo, int i)
{
	char	quote;

	while (str[i])
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
				str[i] = 127;
			dqo = 0;
			sqo = 0;
		}
		if (str[i])
			i++;
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
