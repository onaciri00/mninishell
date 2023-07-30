/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:28:18 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/07/30 13:39:23 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

int    execute_builtins(t_lexer *cmd)
{
    int i;

    i = 0;
    if(ft_strcmp(cmd->cmd[0], "pwd") == 0)
    { 
        i++;
        ft_pwd();
    }
    else if(ft_strcmp(cmd->cmd[0], "echo") == 0)
        ft_echo(&cmd->cmd[0]);
    else if(ft_strcmp(cmd->cmd[0], "exit") == 0)
    {
        i++;
        ft_exit(&cmd->cmd[0]);
    }
    // else if(ft_strcmp(cmd->cmd[0], "foobar") == 0)
    // {
    //     i++;
    //     for (int j = 0; cmd->cmd[j] != NULL; j++)
    //         printf("%s\n", cmd->cmd[j]) ;
    // }
    if(ft_strcmp(cmd->cmd[0], "cd") == 0)
    {
        i++;
        cd(cmd->cmd, &(cmd->env));
    }
    return (i);
}