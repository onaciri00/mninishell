/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 08:11:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/26 11:43:27 by onaciri          ###   ########.fr       */
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

	lst = cmd->file;
	while (lst)
	{
		if (lst->limeter)
			free(lst->limeter);
		else if (lst->file)
			free(lst->file);
		lst = lst->next;
	}
	while (cmd->file)
	{
		lst = cmd->file->next;
		free(cmd->file);
		cmd->file = lst;
	}
	while (cmd)
	{
		free_2d(cmd->cmd);
		keep = cmd->next;
		free(cmd);
		cmd = keep;
	}
}