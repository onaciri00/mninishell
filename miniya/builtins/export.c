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
            return (env->value);
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
    new_env->value = ft_strdup(value);
    new_env->next = NULL; // kanzidi wahd nod f lekher dyal struct (env)
    if (*env == NULL)
        *env = new_env;
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
            free(temp->value);
            temp->value = ft_strdup(value);// kancopie la valeur jdida
            return;
        }
        temp = temp->next;
    }
}


/** print_env()
{
    t_env *tmp

    while (tmp)
    {
        printf("%s=%s", tmp->key, tmp->value);
    
    }
}
**/

// sort

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
        current->next = NULL;
        insert_sorted(&sorted_list, current);
        current = next;
    }

    while (sorted_list != NULL) 
    {
        printf("declare -x %s=\"%s\"\n", sorted_list->key, sorted_list->value);
        sorted_list = sorted_list->next;
    }
}

int ft_export(char **cmd, t_env **env)
{
    char    *found;
    int     i;
    t_env   *tmp;
    char    **arg;

    if (cmd[1] == NULL)
    {
        tmp = (*env);
        while (tmp)
        {
            // printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            // tmp = tmp->next;
            print_export_sorted(tmp);
        }
        return (0);
    }
    i = 1;

    while (cmd[i])
    {
        arg = env_split(cmd[i]); // cmd: key=value | arg[0] : key | arg[1] : value

        found = get_env(*env, arg[0]);
        if (!found)
            append_env(arg[0], arg[1], env);
        else
            update_env(arg[0], arg[1], env);
        i++;
    }
    return (0);
}