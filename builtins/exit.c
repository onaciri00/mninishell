/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:36:17 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/07/29 13:36:02 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"


void	ft_exit(char **str)
{
	int				i;
	unsigned char	exit_code;
	int flag = 0;
	i = 0;
	
   
	if (str[1])
	{
		while(str[1][i])
		{
			if(ft_isdigit(str[1][i]))
				flag = 1;
			i++;
		}
	}
	
 	if (str[0] && !str[1])
    {
        printf("exit\n");
        exit(0);
    }

	else if (str[1])
	{
    	if (!flag)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", str[1]);
			exit(255);
		}
		else if(flag && !str[1])
		{
			printf("exit\n");
			exit_code = atoi(str[1]);
			exit(exit_code);
		}
		else if(flag && str[2])
			printf("exit\nminishell: exit: too many arguments\n");
		else if (flag)
		{
			printf("exit\n");
			exit_code = atoi(str[1]);
			exit(exit_code);
		}
	}
}