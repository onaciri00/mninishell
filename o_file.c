/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:20:35 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/24 05:56:33 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	open_her(char *str)
{
	char	*lim;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	
	while (1)
	{
		lim = readline(">");
		if (ft_strlen(lim) == (ft_strlen(str) && ft_strncmp(lim, str, ft_strlen(lim))))
			break;
		write(fd[1], lim, ft_strlen(lim));
		free(lim);
	}
	free(lim);
	close(fd[1]);
	return(fd[0]);
}

void	open_file(t_lexer *cmd, t_file *file)
{
	t_file	*new;
	int		fd;

	new = file;
	while (new)
	{
		if (new->file)
		{
			if (new->type == 0)
				fd = open(new->file, O_RDONLY);
			else if (new->type == 1)
				fd = open(new->file, O_CREAT | O_RDWR | O_APPEND, 0666);
			else if (new->type == 3)
				fd = open(new->file, O_CREAT | O_RDWR | O_TRUNC, 0666);
		}
		else if (new->limeter)
			fd = open_her(new->limeter);
		if (fd == -1 && new->file)
			printf("PROBLEM IN OPENING %s\n", new->file);
		else if (fd == -1 && new->limeter)
			printf("PROBLEM IN OPENING HERDOC\n");
		if (new->type == 0 || new->type == 2)
			cmd->inf = fd;
		else if (new->type == 3 || new->type == 1)
			cmd->outf = fd;
		new = new->next;
	}
}