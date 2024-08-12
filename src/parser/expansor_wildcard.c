#include "../../inc/minishell.h"


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

t_token *allocate_token(void)
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
        if (ft_fnmatch(pattern, entry->d_name) == 0)
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