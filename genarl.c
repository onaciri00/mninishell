/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genarl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 08:24:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/05 06:11:22 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	file_size(t_file *file)
{
	int	i;

	i = 0;
	if (!file)
		return (0);
	while (file)
	{
		file = file->next;
		i++;
	}
	return (i);
}

t_file	*new_file(t_file **file)
{
	t_file	*lst;
	t_file	*new;

	if (!*file)
	{
		(*file) = malloc(sizeof(t_file));
		(*file)->next = NULL;
		(*file)->limeter = NULL;
		(*file)->file = NULL;
		(*file)->type = -1;
		return (*file);
	}
	else
	{
		lst = (*file);
		while (lst->next)
			lst = lst->next;
		new = malloc(sizeof(t_file));
		new->next = NULL;
		new->limeter = NULL;
		new->file = NULL;
		new->type = -1;
		lst->next = new;
		return ((new));
	}
}

int	len_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_lexer	*creat_cmd(int size)
{
	t_lexer	*cmd;
	t_lexer	*lst;

	if (!size)
		return (NULL);
	cmd = malloc(sizeof(t_lexer));
	cmd->file = NULL;
	cmd->inf = -2;
	cmd->outf = -2;
	cmd->size = 0;
	lst = cmd;
	while (--size)
	{
		cmd->next = malloc(sizeof(t_lexer));
		cmd->next->file = NULL;
		cmd->next->inf = -2;
		cmd->next->outf = -2;
		cmd->next->size = 0;
		cmd = cmd->next;
	}
	cmd->next = NULL;
	return (lst);
}
