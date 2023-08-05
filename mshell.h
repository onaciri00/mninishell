/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:50:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/08/05 10:31:53 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H

#define MSHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
# include<fcntl.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int exit_s;

typedef struct s_env
{
	char			*key;
    char            *value;
	struct s_env	*next;
}t_env;

typedef struct s_file
{
	int		type;
    char    *limeter;
    int     lim_con;
    char    *file;
    struct s_file *next;
} t_file;
    
typedef struct s_lexer
{
    char	        **cmd;
    int             id;
    t_file	        *file;
	t_env			*env;
    int             inf;
    int             outf;
    int             size;
    struct s_lexer  *next;
    
}	t_lexer;

t_lexer	*ft_start(char **str, t_env *var, int i);
int	    check_err(char *str);
int	    syt_val(char *str);
t_file  *lst_file(t_file *fil);
int     len_2d(char **str);
t_lexer *creat_cmd(int size);
t_file  *new_file(t_file  **file);
void    deqou_cmd(char *str, int sqo, int dqo, int i);
void	env_new(t_env **var, char *env);
t_env	*full_env(char **env);
void	ft_expand(char **str, t_env *env, int v, int i);
int	    is_quote(char *str, int i);
void	showerror(char *str);
void	rem_quote(t_lexer *cmd);
void	open_file(t_lexer *cmd, t_file *file, t_env *env, int fd);
void    free_2d(char **str);
void	pipex(t_lexer  *cmd, char **env, int i);
void	free_all(t_lexer *cmd);
char    **env_split(char *env);
int    execute_builtins(t_lexer *cmd);
int     ft_pwd(void);
int     ft_strcmp(char *s1, char *s2);
void	ft_echo(char **arg);
void    ft_exit(char **cmd);
int     ft_cd(char **arg, t_env **env);
int     ft_export(char **cmd, t_env **env);
void    pre_exe(t_lexer  *cmd, char **env);
void	children(t_lexer *cmd, char **env,  int i, int o_out);
int     is_built(char *str);
char    **extra_check(char *str);
char    *ft_strextra(char **str);
char	*ft_path(char *path_cmd, t_env *env);

#endif