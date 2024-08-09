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

char *construct_full_path(const char *dir_path, const char *entry_name)
{
    char *full_path = malloc(2048);
    if (!full_path)
    {
        perror("malloc");
        return NULL;
    }
    snprintf(full_path, 2048, "%s/%s", dir_path, entry_name);
    return full_path;
}

t_token *allocate_token()
{
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
    {
        perror("malloc");
        return NULL;
    }
    new_token->next = NULL;
    return new_token;
}

int initialize_token(t_token *token, const char *full_path)
{
    token->token = strdup(full_path);
    if (!token->token)
    {
        perror("strdup");
        free(token);
        return -1;
    }
    token->type = ARG;
    token->is_quote = 0;
    return 0;
}

t_token *create_token_from_entry(const char *dir_path, const char *entry_name)
{
    t_token *new_token;
    char *full_path;
    
    full_path = construct_full_path(dir_path, entry_name);
    if (!full_path)
        return NULL;

    new_token = allocate_token();
    if (!new_token)
    {
        free(full_path);
        return NULL;
    }

    if (initialize_token(new_token, full_path) < 0)
    {
        free(full_path);
        return NULL;
    }

    free(full_path);
    return (new_token);
}

t_token *match_wildcards_in_directory(const char *dir_path, const char *pattern)
{
    DIR *dir;
    struct dirent *entry;
    t_token *new_tokens;
    t_token *last_token;
    t_token *new_token;

    new_tokens = NULL;
    last_token = NULL;
    // Open the target directory for reading
    dir = opendir(dir_path);
    if (!dir)
        return (perror("💩 nugget 🐾"), NULL);

    // Iterate over directory entries
    while ((entry = readdir(dir)) != NULL) 
    {
        if (!ft_strncmp(entry->d_name, ".") || !ft_strncmp(entry->d_name, ".."))
            continue;

        // Use custom fnmatch logic to match wildcard patterns
        if (my_fnmatch(pattern, entry->d_name) == 0)
        {
            new_token = create_token_from_entry(dir_path, entry->d_name);
            if (new_token) 
            {
                // Add the new token to the linked list
                if (!new_tokens)
                    new_tokens = new_token;
                else
                    last_token->next = new_token;
                last_token = new_token;
            }
        }
    }

    closedir(dir);
    return new_tokens;
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
        strncpy(dir_path, pattern, dir_len);
        dir_path[dir_len] = '\0';
        pattern = slash_pos + 1;
    }
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
