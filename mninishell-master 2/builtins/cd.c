/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:07:09 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/07/29 19:03:26 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

// char	*get_path(t_env **env, char **argv)
// {
// 	char	*path;

// 	path = NULL;
// 	if ((!ft_strcmp(argv[0], "cd") && (!ft_strcmp(argv[1], "~")))
// 		|| (!ft_strcmp(argv[0], "cd") && (argv[1] == NULL)))
// 	{
// 		path = get_value(env, "HOME") + 1;
// 		if (!path)
// 			printf("minishell: cd: HOME not set");
// 	}
// 	else if (!ft_strcmp(argv[0], "cd") && (!ft_strcmp(argv[1], "-")))
// 	{
// 		path = get_value(env, "OLDPWD") + 1;
// 		if (!path)
// 			printf("minishell: cd: HOME not set");
// 	}
// 	else
// 		path = argv[1];
// 	return (path);
// }

// char	*get_value(t_env **env, char *name)
// {
// 	t_env	*value2;

// 	value2 = *env;
// 	while (value2 && ft_strcmp(value2->name, name))
// 		value2 = value2->next;
// 	if (value2 && value2->var)
// 		return (value2->var);
// 	return (NULL);
// }

// void	go_to_home(t_env **env)
// {
// 	char	*pwd;
// 	char	*oldpwd;

// 	pwd = get_value(env, "PWD");
// 	oldpwd = get_value(env, "OLDPWD");
// 	if (!oldpwd)
// 		return ;
// 	upd_oldpwd(env, pwd);
// }

// int	upd_oldpwd(t_env **env, char *pwd)
// {
// 	t_env	*cur;

// 	cur = *env;
// 	while (cur && ft_strcmp(cur->name, "OLDPWD"))
// 		cur = cur->next;
// 	if (cur && cur->var)
// 	{
// 		cur->var = NULL;
// 		if (pwd)
// 			cur->var = pwd;
// 		else
// 			cur->var = ft_strdup("=");
// 	}
// 	if (!pwd)
// 		return (1);//ou cas ou pwd n'existe pas on a besoin de changer oldpwd.
// 	cur = *env;
// 	pwd = getcwd(NULL, 0);
// 	while (cur && ft_strcmp(cur->name, "PWD"))
// 		cur = cur->next;
// 	if (cur && cur->var)
// 	{
// 		cur->var = NULL;
// 		cur->var = ft_strjoin("=", pwd);
// 	}
// 	return (0);
// }

// int	ft_cd(t_env **env, char **argv)
// {
// 	char	*path;

// 	path = get_path(env, argv);
// 	if (!path)
// 		return (1);
// 	if (chdir(path) == -1)
// 	{
// 		printf("minishell: cd: %s : No such file or directory\n", path);
// 		return (1);
// 	}
// 	go_to_home(env);
// 	return (0);
// }

static int check_error(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
        i++;
    return (i);
}

int cd(char **arg, t_env **env)
{
    if (check_error(arg) != 2) // khas tckoun cd w argument wa7ed
    {
        printf("Error: too many arguments\n");
        return (1); // hna anwaliw ndiro exit status f ga3 builtins
    }
    (void)env;
    if (chdir(arg[1]) == -1) {
        perror("Error");
        return 1;
    }
    printf("Directory changed to: %s\n", arg[1]);
    return 0;
}