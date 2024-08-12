#include "../../inc/minishell.h"

static void tokenize_env(t_token **tmp2, t_token **tmp, t_token **head)
{
    char *env;
    t_token *new_tokens;

    env = getenv((*tmp)->token);
    if(!env)
        env = ft_strdup("");
    else
        env = ft_strdup(env);
    new_tokens = tokenizer(env);
    if (new_tokens)
    {
        add_top(*tmp2, new_tokens);
        erase_one(head, *tmp2);
        *tmp = new_tokens;
    }
    else
    {
        free((*tmp2)->token);
        (*tmp2)->token = env;
    }
}

static void tokenize_wildcards(t_token **tmp2, t_token **tmp, t_token **head)
{
    char *pattern;
    char dir_path[1024] = ".";
    char *slash_pos;
    size_t dir_len;
    t_token *new_tokens;

    pattern = (*tmp)->token;
    slash_pos = ft_strrchr(pattern, '/');
    if (slash_pos)
    {
        dir_len = slash_pos - pattern;
        dir_len++;
        ft_strlcpy(dir_path, pattern, dir_len);
        dir_path[dir_len] = '\0';
        pattern = slash_pos + 1;
    }
    printf("pattern: %s\n", dir_path);
    new_tokens = match_wildcards_in_directory(dir_path, pattern);
    if (new_tokens)
    {
        add_top(*tmp2, new_tokens);
        erase_one(head, *tmp2);
        *tmp = new_tokens;
    }
}

t_token *expansor(t_token *head)
{
    t_token *tmp = head;
    t_token *tmp2;
    while (tmp)
    {
        if (tmp->type == ENV)
        {
            tmp2 = tmp;
            tokenize_env(&tmp2, &tmp, &head);
        }
        // AQUI EMPIEZA EL EXPANSOR DE WILDCARDS
        else if(tmp->type == ARG && ft_strchr(tmp->token, '*'))
        {
            tmp2 = tmp;
            tokenize_wildcards(&tmp2, &tmp, &head);
        }
        tmp = tmp->next;
    }
    return head;
}
