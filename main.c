/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:44:20 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/27 07:28:32 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mshell.h"

int main(int ac, char *av[], char *env[]) 
{
    char *str;
	t_lexer *cmd;
	//t_file *file;
	t_env	*var;
	//int i;

	if (ac != 1 || !ft_strnstr(av[0], "./minishell", 11))
		return (1);
	while (1)
	{
		str = readline("minshell: ");
		if (!str)
			exit(10);
		if(str[0])
		{
			add_history(str);
			var = full_env(env);
			cmd = ft_start(str, var);
			pipex(cmd, env);
			//free_all(cmd);
		}
		// while (cmd)
		// {
		//  	i = -1;
		// 	while (cmd->cmd[++i])
		// 		printf("*%s* ", cmd->cmd[i] /*cmd->file->file*/);
		// 	file = cmd->file;
		// 	printf("\n");
		// 	while (file)
		// 	{
		// 		if (file->file)
		// 			printf("\n********** file ='%s' %d\n", file->file, file->type);
		// 		else	
		// 			printf("********** lim ='%s' %d\n", file->limeter, file->type);
		// 		file = file->next;
		// 	}
		// 	cmd = cmd->next;
		// }
	}
}
