#include "../../inc/minishell.h"

void tokenize_env(t_token **tmp2, t_token **tmp, t_token **head, t_env **envp)
{
    char *env;
    t_token *new_tokens;

    env = ft_getenv((*tmp)->token, *envp);
    if(!env)
        env = ft_strdup("");
    else
        env = ft_strdup(env);
    new_tokens = tokenizer(env, *envp);
    if (new_tokens)
    {
        add_top(*tmp2, new_tokens);
        erase_one(head, *tmp2);
        *tmp = new_tokens;
        free(env);
	    env = NULL;
    }
    else
    {
        free((*tmp2)->token);
        (*tmp2)->token = env;
    }
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

static char *change_status(t_token *head, t_env **env)
{
    t_token *tmp;
    char *new_token;

    tmp = head;

    while(tmp->type != EXIT_STATUS)
        tmp = tmp->next;
    new_token = ft_itoa((*env)->exit_status);
    free(tmp->token);
    tmp->token = new_token;
    return (tmp->token);
}

t_token *expansor(t_token *head, t_env **env, int is_hdoc, int is_quoted)
{
    t_token *tmp = head;
    t_token *tmp2;

    if(is_hdoc)
        return(expansor_hdoc(head, env, is_hdoc, is_quoted));
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
            tmp->token = clean_quotes(tmp);
        if(tmp->type == EXIT_STATUS)
            tmp->token = change_status(head, env);
        tmp = tmp->next;
    }
    return head;
}
