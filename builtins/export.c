/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:53:44 by sel-ouar          #+#    #+#             */
/*   Updated: 2023/08/03 10:15:59 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../mshell.h"

// new functions to add :
// sort_env
// append_env
// update_env

// t_env *sort_env(t_env **env) // sort env alphabetic order
// {

// }

char *get_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->key);
        env = env->next;
    }
    return (NULL);
}

void append_env(char *key, char *value, t_env **env) // char *key, char *value
{
    t_env *temp;
    t_env *new_env = (t_env *)malloc(sizeof(t_env));

    if (!new_env) 
    {
        printf("Erreur d'allocation de mémoire.\n");
        return;
    }
    new_env->key = ft_strdup(key);
    if (value)
        new_env->value = ft_strdup(value);
    else
        new_env->value = NULL;
    new_env->next = NULL; // kanzidi wahd nod f lekher dyal struct (env)
    if (*env == NULL)
        (*env) = new_env;
    else 
    {
        temp = *env;
        while (temp->next != NULL) 
            temp = temp->next;
        temp->next = new_env;
    }
}
void update_env(char *key, char *value, t_env **env) // char *key, char *value
{
    t_env *temp = *env;


    while (temp != NULL) 
    {
        if (ft_strcmp(temp->key, key) == 0) {
            if (value)
            {
                free(temp->value);
                temp->value = ft_strdup(value);
            }
            else
                temp->value = NULL;
            return;
        }
        temp = temp->next;
    }
}

void insert_sorted(t_env **head, t_env *node) 
{
    t_env *current;

    if (*head == NULL || strcmp((*head)->key, node->key) >= 0)
    {
        node->next = *head;
        *head = node;
    }
    else
    {
        current = *head;
        while (current->next != NULL && strcmp(current->next->key, node->key) < 0)
            current = current->next;
        node->next = current->next;
        current->next = node;
    }
}

void print_export_sorted(t_env *env)
{
    t_env *sorted_list = NULL;
    t_env *current = env;

    while (current != NULL)
    {
        t_env *next = current->next;
        insert_sorted(&sorted_list, current);
        current = next;
    }

    while (sorted_list != NULL) 
    {
        if (sorted_list->value)
            printf("declare -x %s=\"%s\"\n", sorted_list->key, sorted_list->value);
        else
            printf("declare -x %s=\n", sorted_list->key);
        sorted_list = sorted_list->next;
    }
}

int export_validator(char *arg)
{
    if (arg[0] == '=')
    {
        printf("syntax error\n");
        return (1);
    }
    return (0);
}

int ft_export(char **cmd, t_env **env)
{
    char    *found;
    int     i;
    char    **arg;

    if (cmd[1] == NULL)
    {
        print_export_sorted(*env);
        return (0);
    }
    i = 1;

    while (cmd[i])
    {
        if (export_validator(cmd[i]))
        {
            i++;
            continue;
        }
        arg = env_split(cmd[i]);
        found = get_env(*env, arg[0]);
        if (!found)
            append_env(arg[0], arg[1], env);
        else
            update_env(arg[0], arg[1], env);
        i++;
    }
    return (0);
}
