/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitM.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:04:13 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/27 09:01:14 by onaciri          ###   ########.fr       */
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

void clean_cmd(char *str,int j)
{
	int	i;

	i = 0;
	while (str[i] && i < j)
	{
		str[i] = ' ';
		i++;
	}
}

int	mod_file(char *str, t_file **file, int id)
{
	int		i;
	int		j;
	t_file	*lst;

	i = 0;
	j = 0;
	if (id == 2 || id == 3)
	{	
		j++;
		i++;
	}
	while (str[++i] && str[i] == ' ' && !syt_val(str + i))
		j++;
	while (str[++i] && !syt_val(str + i) && str[i] != ' ');

	lst = new_file(file);
	if (id == 2)
		lst->limeter = ft_substr((const char *)str, j + 1, i - j - 1);
	else if (id != 2)
		lst->file = ft_substr((const char *)str, j+ 1, i - j - 1);
	set_type(id, &lst);
	clean_cmd(str, i);
	return (1);
}


void	check_arg(char *str, t_lexer *cmd, int sqo, int dqo)
{
	int		i;
	char	**ret;

	i = -1;
	while (str[++i])
	{
		if (!sqo && str[i] == '"')
			dqo++;
		if (!dqo && str[i] =='\'')
			sqo++;
		if (sqo == 2 || dqo == 2)
		{
			sqo = 0;
			dqo = 0;
		}
		if (syt_val(str + i) == 2 && !dqo && !sqo)
			i += mod_file(str + i, &cmd->file, 2);
		else if (syt_val(str + i) == 3 && !dqo && !sqo)
			i += mod_file(str +i, &cmd->file, 3);
		else if (syt_val(str +i) == 4 && !dqo && !sqo)
			mod_file(str + i, &cmd->file, 1);
		else if (syt_val(str + i) == 5 && !dqo && !sqo)
			mod_file(str + i , &cmd->file, 0);
	}
	//i = 0;
	ret = ft_split(str, ' ');
	//while (ret[i])
	//	printf("%s\n", ret[i++]); 
	cmd->cmd = ret;
	free(str);
}

t_lexer *ft_start(char *str, t_env *var)
{
	int		i;
	int		size;
	char 	**raw;
	t_lexer	*cmd;
	t_lexer	*lst;

	if (str && check_err(str))
		return (NULL);
	str = ft_expand(&str, var, 0);
	raw = ft_split(str, '|');
	i = 0;
	size = len_2d(raw);
	cmd = creat_cmd(size);
	lst = cmd;
	while (raw[i])
	{
		
		check_arg(raw[i], cmd, 0, 0);
		rem_quote(cmd);
		open_file(cmd, cmd->file, var);
		cmd = cmd->next;
		i++;
	}
	return (lst);
}