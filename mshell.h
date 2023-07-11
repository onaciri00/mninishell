/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:50:19 by onaciri           #+#    #+#             */
/*   Updated: 2023/07/10 11:10:06 by onaciri          ###   ########.fr       */
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

typedef struct s_file
{
    int     type;
    char    *limeter;
    char    *file;
    int     state;
    struct s_file *next;
} t_file;
    
typedef struct s_lexer
{
    char	        *cmd;
    t_file	        *file;
    struct s_lexer  *next;
    
}	t_lexer;

t_lexer *ft_start(char **env, char *str);
int	check_err(char *str);
int	syt_val(char *str);
t_file  *lst_file(t_file *fil);
int len_2d(char **str);
t_lexer *creat_cmd(int size);
t_file *new_file(t_file  **file);

#endif