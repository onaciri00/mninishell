/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:20:35 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/03 07:31:31 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	open_her(char *str, int v, t_env *var)
{
	char	*lim;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		lim = readline(">");
		if (!lim || (ft_strlen(lim) == ft_strlen(str)
				&& !ft_strncmp(lim, str, ft_strlen(lim))))
			break ;
		if (!v)
			ft_expand(&lim, var, 1);
		write(fd[1], lim, ft_strlen(lim));
		write(fd[1], "\n", 1);
		free(lim);
	}
	close(fd[1]);
	return (free(lim), fd[0]);
}

void	set_files(t_lexer *cmd, t_file *new, int fd)
{
	if (new->type == 0 || new->type == 2)
	{
		close(cmd->inf);
		cmd->inf = fd;
	}
	else if (new->type == 3 || new->type == 1)
	{
		close(cmd->outf);
		cmd->outf = fd;
	}
}

void	open_file(t_lexer *cmd, t_file *file, t_env *env)
{
	t_file	*new;
	int		fd;

	new = file;
	fd = -2;
	while (new)
	{
		if (new->file)
		{
			if (new->type == 0)
				fd = open(new->file, O_RDONLY);
			else if (new->type == 1)
				fd = open(new->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			else if (new->type == 3)
				fd = open(new->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		else if (new->limeter)
			fd = open_her(new->limeter, file->lim_con, env);
		if (fd == -1 && new->file)
			printf(" %s: No such file or directory\n", new->file);
		else if (fd == -1 && new->limeter)
			printf("PROBLEM IN OPENING HERDOC\n");
		set_files(cmd, new, fd);
		new = new->next;
	}
}
