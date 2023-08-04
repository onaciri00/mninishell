/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:19:08 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/04 09:55:55 by onaciri          ###   ########.fr       */
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

int	ft_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || str[ft_strlen(str) - 1] == '|')
		return (write(2, "syntax error near unexpected token `|'\n", 39), 1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && is_quote(str, i))
		{
			i++;
			if ((str[i] == '|' && str[i + 1] == '|' ) || !str[i + 1])
			{
				write(2, "syntax error near unexpected token `||'\n", 39);
				return (1);
			}
			while(str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '|')
			{
				write(2, "syntax error near unexpected token `|'\n", 39);
				return (1);
			}
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
		return (write(2, "unclosed Quote\n", 14));
	if (ft_pipe(str))
		return (1);
	if (ft_red(str))
		return (1);
	return (0);
}