/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:19:08 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/05 08:58:45 by onaciri          ###   ########.fr       */
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

int	ft_pipe(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || str[ft_strlen(str) - 1] == '|')
		return (write(2, "syntax error near unexpected token `|'\n", 39), 1);
	while (str[i] && str[++i])
	{
		if (str[i] == '|' && !is_quote(str, i))
		{
			i++;
			if ((str[i] == '|' && str[i + 1] == '|' ) || !str[i + 1])
				return (write(2, "syntax error near unexpected token `||'\n", 39), 1);
			while(str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '|')
				return (write(2, "syntax error near unexpected token `|'\n", 39),1);
		}
	}
	return (0);
}

int	ft_red(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && !is_quote(str, i))
		{
			if (str[i + 1] == '>')
				i++;
			i++;
			while (str[i] == ' ')
				i++;
			if (!str[i]|| str[i] == '>' || str[i] == '<' || str[i] == '|')
				return (write(2, "syntax error near unexpected token > \n", 40),1);
		}
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			i++;
			while (str[i] == ' ')
				i++;
			if (!str[i]|| str[i] == '>' || str[i] == '<' || str[i] == '|')
				return (write(2, "syntax error near unexpected token < \n", 40), 1);
		}
	}
	return (0);
}

int	check_err(char *str)
{
	if (is_quote(str, ft_strlen(str) - 1))
	{
		exit_s = 258;
		return (write(2, "unclosed Quote\n", 14), 1);
	}
	if (ft_pipe(str, 0))
	{
		exit_s = 258;
		return (1);
	}
	if (ft_red(str))
	{
		exit_s = 258;
		return (1);
	}
	return (0);
}