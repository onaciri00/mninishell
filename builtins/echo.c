/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:06:10 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/08/02 16:13:46 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

int check_n(char *s)
{
	int i ;
	if(s[0] == '-')
		s++;
	i = 0;
	while(s[i])
	{
		if(s[i] != 'n')
			return (0);
		i++;
	}	
	return (1);
}

void	ft_echo(char **cmd)
{
	int	new_line;
	int	i;
	
	cmd++;
	if (cmd[0] && check_n(cmd[0]))
	{
		new_line = 0;
		i = 1;
	}
	else
	{
		new_line = 1;
		i = 0;
	}
	while (cmd && cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}