/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:19:08 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/14 14:39:08 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

int	syt_val(char *str)
{
	if (str[0] == '|')
		return (1);
	else if (str[0] == '<' && str[1] == '<')
		return (2);
	else if (str[0] == '>' && str[1] =='>')
		return (3);
	if (str[0] == '>')
		return (4);
	else if (str[0] == '<')
		return (5);
	return (0);
}

int	check_qou(char *str)
{
	int	i;
	int	dqo;
	int	sqo;

	i = -1;
	dqo = 0;
	sqo = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !sqo)
			dqo++;
		else if (str[i] == '\'' && !dqo)
			sqo++;
		if (dqo == 2)
			dqo = 0;
		if (sqo == 2)
			sqo = 0;
	}
	if (dqo == 1 || sqo == 1)
		return (-1);
	return (i);
}

int	err_qou(char *str)
{
	int	i;

	i = check_qou(str);
	if (syt_val(str) == 1)
		return (printf("syntax error: pipe at the start\n"),1);
	else if (i == -1)
		return (printf("syntax error: unclosed Quote\n"), 1);
	else if (syt_val(str + (i - 1)))
		return (printf("syntax error: unexpected end of file\n"),1);
	return (0);
}


int	err_red(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !j)
			j++;
		else if (str[i] == '\'' && !j)
			j++;
		if (j == 2)
			j = 0;
		if (syt_val(str + i) && !j)
		{
			if (syt_val(str + i) == 2 || syt_val(str + i) == 3)
				i++;
			while(str[++i] == ' ');

			if (syt_val(str + i) || !str[i])
				return (printf("syntax error near: %c\n", str[i]) ,1);
		}
	}
	return (0);
}

int	check_err(char *str)
{
	if (err_qou(str) || err_red(str))
		return (1);
	return (0);
}