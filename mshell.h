/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:50:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/20 12:28:01 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H

#define MSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}t_env;

typedef struct s_file
{
	int		type;
    char    *limeter;
    char    *file;
    int     state;
    struct s_file *next;
} t_file;
    
typedef struct s_lexer
{
    char	        *cmd;
    t_file	        *file;
	t_env			*env;
    struct s_lexer  *next;
    
}	t_lexer;

t_lexer *ft_start(char *str, t_env *var);
int	    check_err(char *str);
int	    syt_val(char *str);
t_file  *lst_file(t_file *fil);
int     len_2d(char **str);
t_lexer *creat_cmd(int size);
t_file  *new_file(t_file  **file);
void    deqou_cmd(char *str, int i);
void	env_new(t_env **var, char *env);
t_env	*full_env(char **env);
char*    ft_expand(char *str, t_env *env, int dqo, int sqo);
int	is_quote(char *str, int i);

#endif