/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 08:11:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/01 09:24:49 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mshell.h"

void    free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str); 
}

void	free_all(t_lexer *cmd)
{
	t_file *lst;
	t_lexer	*keep;

	while (cmd)
	{
		if (cmd->cmd)
			free_2d(cmd->cmd);
		lst = cmd->file;
		while (lst)
		{
			if (lst->limeter)
				free(lst->limeter);
			if (lst->file)
				free(lst->file);
			cmd->file = lst;
			lst = lst->next;
			free(cmd->file);
		}
		keep = cmd->next;
		free(cmd);
		cmd = keep;
	}
}