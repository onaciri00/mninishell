/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:06:10 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/07/29 14:31:03 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void	ft_echo(char **cmd)
{
	int	new_line;
	int	i;

	if (ft_strcmp(cmd[0], "-n") == 0)
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
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}