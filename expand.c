/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:44:09 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/21 09:44:46 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	env_new(t_env **var, char *env)
{
	t_env	*lst;
	t_env	*new;

	if (!*var)
	{
		(*var) = malloc(sizeof(t_env));
		(*var)->var = env;
		(*var)->next = NULL;
	}
	else
	{
		lst = (*var);
		while (lst->next)
			lst = lst->next;
		new = malloc(sizeof(t_env));
		new->next = NULL;
		new->var = env;
		lst->next = new;
	}
}

t_env	*full_env(char **env)
{
	t_env	*var;
	int		i;

	i = -1;
	var = NULL;
	while (env[++i])
	{
		env_new(&var, env[i]);
	}
	return (var);
}


char *ft_findvar(char *str, int start, int end, t_env *env)
{
	t_env	*var;
	size_t		i;
	char	*tmp;
	//char	**spl;

	if (!env)
		return (ft_strdup(""));	
	tmp = ft_substr(str, start, end - start);
	printf("********%s j =%d i =%d\n", tmp, start, end);
	var = env;
	while (var)
	{
		i = -1;
		while (var->var[++i] && var->var[i] != '=');

		if (!ft_strncmp(tmp, var->var, ft_strlen(tmp)) && i == ft_strlen(tmp))
		{
			free(tmp);
			tmp = ft_substr(var->var, ft_strlen(tmp) + 1, ft_strlen(var->var) - ft_strlen(tmp));
			
			return (tmp);
		}
		var = var->next;
	}
	return (ft_strdup(""));
}

void	rem_dollare(char **str, int *i, int *j)
{
	int	k;
	int	num;
	int	dol;

	k = *i + 1;
	dol = 0;
	num = 0;
	while ((*str)[++k] && (*str)[k] >= 32 && (*str)[k] <= 35)
	{
		if ((*str)[k] == '$')
			dol++;
		if ((*str)[k] >= 48 && (*str)[k] <= 57)
			num++;	
	}
}

int	ft_strmerge(char **str, int i, int j, t_env *env)
{
	char	*str_bef;
	char	*str_aft;
	char	*tmp2;
	int		z;

	rem_dollare(str, &i, &j);
	while ((*str)[++i])
		if (((*str)[i] >= 38 && (*str)[i]  <= 64 )|| ((*str)[i] >= 32 && (*str)[i] <= 47)|| syt_val(*str + i))
			break;
	str_bef = ft_substr(*str, 0, j - 1);
	str_aft = ft_substr(*str, i + j, ft_strlen(*str) - j);
	if ((*str)[i] != '$' && i != j)
		tmp2 = ft_findvar(*str, j, i, env);
	else
		tmp2 = ft_strdup("");
	free(*str);
	*str = ft_strjoin(str_bef, tmp2);
	z = ft_strlen(tmp2);
	tmp2 = ft_strjoin(*str, str_aft);
	*str = tmp2;
	return (j + z - 1);
}

int	do_expand(char *str, int i)
{	
	while (--i >= 0 && str[i])
		if (str[i] != ' ')
			break;
	if (i <= 0)
	{
		if (syt_val(str) == 2)
			return (0);
	}
	else
		if (syt_val(str + (i - 1)) == 2)
			return (0);
	return (1);
}

char   *ft_expand(char *str, t_env *env, int dqo, int sqo)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[i] == '"' && !sqo)
			dqo++;
		else if (str[i] == '\'' && !dqo)
			sqo++;
		if (sqo == 2 || dqo == 2)
		{
			sqo = 0;
			dqo = 0;
		}
        if (str[i] == '$' && str[i + 1] /*&& str[i + 1] != '$' &&*/ && str[i + 1] != '"' && str[i +1] != ' ')
		{
			if (sqo != 1 && do_expand(str , i))
				i = ft_strmerge(&str, i, i + 1, env);
		}
		if (str[i])
			i++;
	}
	return (str);
}