#include "../../inc/minishell.h"


static char *construct_full_path(const char *dir_path, const char *entry_name)
{
    char *full_path = malloc(2048);
    if (!full_path)
    {
        perror("malloc");
        return NULL;
    }
    ft_strlcpy(full_path, dir_path, PATH_MAX);
    ft_strlcat(full_path, "/", PATH_MAX);
    ft_strlcat(full_path, (char *)entry_name, PATH_MAX);
    return full_path;
}

static t_token *allocate_token(void)
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

static int initialize_token(t_token *token, const char *full_path)
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
        return (free(full_path), NULL);

    if (initialize_token(new_token, full_path) < 0)
        return (free(full_path), NULL);

    return (free(full_path), new_token);
}

t_token *match_wildcards_in_directory(const char *dir_path, const char *pattern)
{
    DIR *dir;
    t_token *new_tokens;
    t_token *last_token;

    dir = open_directory(dir_path);
    if (!dir)
        return (NULL);
    last_token = NULL;
    new_tokens = NULL;
    printf("Matching pattern %s in directory %s\n", pattern, dir_path);
    process_directory_entries(dir, pattern, &new_tokens, &last_token);

    closedir(dir);
    return new_tokens;
}