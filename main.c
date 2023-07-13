/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/13 07:24:03 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int main(int ac, char *av[], char *env[]) 
{
    char *str;
	t_lexer *cmd;
	t_file *file;
	int	i;
	if (ac != 1 || !ft_strnstr(av[0], "./minishell", 11))
		return (1);
	while (1)
	{
		str = readline("minshell: ");
		if(!str)
			exit(1);
		cmd = ft_start(env, str);
		while (cmd)
		{
		 	printf("%s\n", cmd->cmd /*cmd->file->file*/);
		 	file = cmd->file;
			//printf("*****ile = %s %d*****\n", file->file, file->type);
			i = 0;
			while (file)
			{
				i++;
				if (file->file)
					printf("********** file = %s %d\n", file->file, file->type);
				else	
					printf("********** lim = %s %d\n", file->limeter, file->type);
				file = file->next;
			}
			cmd = cmd->next;
		}
		free(str);
	}
	(void)env;
}
