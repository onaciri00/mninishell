/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:28:18 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/08/01 11:57:15 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

int    execute_builtins(t_lexer *cmd)
{
    if(ft_strcmp(cmd->cmd[0], "pwd") == 0)
    { 
        ft_pwd();
        return (1);
    }
    else if(ft_strcmp(cmd->cmd[0], "echo") == 0)
    {
        ft_echo(&cmd->cmd[1]);
        return (1);
    }
    else if(ft_strcmp(cmd->cmd[0], "exit") == 0)
    {
        ft_exit(&cmd->cmd[0]);
        return (1);
    }
    if(ft_strcmp(cmd->cmd[0], "cd") == 0)
    {
        cd(cmd->cmd, &(cmd->env));
        return (1);
    }
    if(ft_strcmp(cmd->cmd[0], "export") == 0)
    {
        ft_export(cmd->cmd, &(cmd->env));
        return (1);
    }
    if(ft_strcmp(cmd->cmd[0], "env") == 0)
    {
        ft_env(cmd->cmd, cmd->env);
        return (1);
    }
    return (0);
}