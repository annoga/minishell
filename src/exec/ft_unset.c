#include "../../inc/minishell.h"

static void erase_two(t_env **head, t_env *to_erase);
static void free_two_env(t_env *env);

int ft_unset(const char *key_name, t_env **env)
{
    t_env *tmp = *env;
    t_env *next;

    while (tmp)
    {
        next = tmp->next;
        if (ft_strcmp(tmp->key_name, key_name) == 0)
        {
            erase_two(env, tmp);
            break;
        }
        tmp = next;
    }
    return 0;
}

static void free_two_env(t_env *env) {
    if (env) {
        free(env->key_name);
        env->key_name = NULL;
        free(env->value);
        env->value = NULL;
        free(env);
    }
}

static void erase_two(t_env **head, t_env *to_erase)
{
    t_env *aux;
    t_env *prev;

    if (!head || !*head || !to_erase)
        return;

    if (*head == to_erase)
    {
        *head = to_erase->next;
        free_two_env(to_erase);
        return;
    }
    prev = *head;
    aux = (*head)->next;
    while (aux)
    {
        if (aux == to_erase)
        {
            prev->next = aux->next;
            free_two_env(aux);
            return;
        }
        prev = aux;
        aux = aux->next;
    }
}
