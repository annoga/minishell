#include "../../inc/minishell.h"

static void tokenize_env(t_token **tmp2, t_token **tmp, t_token **head, t_env **envp)
{
    char *env;
    t_token *new_tokens;

    // env = getenv((*tmp)->token);
    env = ft_getenv((*tmp)->token, *envp);
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
	free(env);
	env = NULL;
}

static void tokenize_wildcards(t_token **tmp2, t_token **tmp, t_token **head)
{
    t_token *new_tokens;

    new_tokens = handle_input((*tmp)->token);
    if (new_tokens)
    {
        add_top(*tmp2, new_tokens);
        erase_one(head, *tmp2);
        *tmp = new_tokens;
    }
}

static char *clean_quotes(t_token *head)
{
    t_token *tmp;
    char *new_token;

    tmp = head;
    if(tmp->type == SINGLE_QUOTE)
    {
        new_token = ft_strtrim(tmp->token, "\'");
        free(tmp->token);
        tmp->token = new_token;
    }
    else if(tmp->type == DOUBLE_QUOTE)
    {
        new_token = ft_strtrim(tmp->token, "\"");
        free(tmp->token);
        tmp->token = new_token;
    }
    return (tmp->token);
}

t_token *expansor(t_token *head, t_env **env)
{
    t_token *tmp = head;
    t_token *tmp2;
    while (tmp)
    {
        if (tmp->type == ENV)
        {
            tmp2 = tmp;
            tokenize_env(&tmp2, &tmp, &head, env);
        }
        else if(tmp->type == ARG && ft_strchr(tmp->token, '*'))
        {
            tmp2 = tmp;
            tokenize_wildcards(&tmp2, &tmp, &head);
        }
        if(tmp->type == SINGLE_QUOTE || tmp->type == DOUBLE_QUOTE)
        {
            tmp->token = clean_quotes(tmp);
        }
        tmp = tmp->next;
    }
    return head;
}
