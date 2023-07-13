/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitM.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:04:13 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/13 07:32:52 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	set_type(int id, t_file **file)
{
	if (id == 0)
		(*file)->type = 0;
	else if (id == 1)
		(*file)->type = 1;
	else if(id == 2)
		(*file)->type = 2;
	else if (id == 3)
		(*file)->type = 3;
}

int	mod_file(char *str, t_file **file, int id, int z)
{
	int		i;
	int		j;
	t_file	*lst;

	i = 0;
	j = 0;
	while (str[++i] && !syt_val(str + i))
	{
		if (str[i] != ' ')
			z++;
		while (str[i] && str[i] == ' ' && !z)
		{	
			j++;
			i++;
			if (str[i + 1] && str[i + 1] != ' ')
				break;
		}
		if (z && str[i] == ' ')
			break;
	}
	if (syt_val(str + j))
		j++;
	lst = new_file(file);
	if (id == 2)
		lst->limeter = ft_substr((const char *)str, j, i - j);
	else if (id != 2)
		lst->file = ft_substr((const char *)str, j, i - j);
	set_type(id, &lst);
	return (1);
}

void clean_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i++])
	{
		if (syt_val(str + i))
		{
			str[i] = ' ';
			while (str[i++] && str[i] != ' ')
				if (str[i])
					str[i] = ' ';
		}
	}
}
void	check_arg(char *str, t_lexer *cmd)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (syt_val(str + i) == 2)  
			i += mod_file(str +(i + 1), &cmd->file, 2, 0);
		else if (syt_val(str + i) == 3)
			i += mod_file(str +(i + 1), &cmd->file, 3, 0);
		else if (syt_val(str +i) == 4)
			mod_file(str + i, &cmd->file, 1, 0);
		else if (syt_val(str + i) == 5)
			mod_file(str + i , &cmd->file, 0, 0);
	}
	clean_cmd(str);
	cmd->cmd = str;
}

t_lexer *ft_start(char **env, char *str)
{
	int		i;
	int		size;
	char 	**raw;
	t_lexer	*cmd;
	t_lexer	*lst;

	i = 0;
	if (str && check_err(str))
		return (NULL);
	deqou_cmd(str, 0, 0, -1);
	raw = ft_split(str, '|');
	size = len_2d(raw);
	cmd = creat_cmd(size);
	lst = cmd;
	while (raw[i])
	{
		check_arg(raw[i], cmd);
		cmd = cmd->next;
		i++;
	}
	(void)env;
	return (lst);
}