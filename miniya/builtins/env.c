/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:29:37 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/08/01 12:07:03 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void    ft_env(char **arg, t_env *env)
{
    t_env   *cmd;

    cmd = env;
    if(arg[1])
        printf("env: No sush file or directory\n");
    else
    {
        while(cmd)
        {
            if(ft_strcmp(cmd->value, "\0") && cmd->key && cmd->value)
            {
                ft_putstr_fd(cmd->key, 1);
                ft_putchar_fd('=', 1);
                if(ft_strcmp(cmd->value, "\"\""))
                    ft_putstr_fd(cmd->value, 1);
                ft_putchar_fd('\n', 1);
            }
            cmd = cmd->next;
        }
    }
}