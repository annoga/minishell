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

// Updated tokenize_wildcards function
void tokenize_wildcards(t_token **tmp2, t_token **tmp, t_token **head) {
    DIR *dir;
    struct dirent *entry;
    t_token *new_tokens = NULL;
    t_token *last_token = NULL;

    char *pattern = (*tmp)->token;
    char dir_path[1024] = ".";
    char *slash_pos = ft_strrchr(pattern, '/');

    if (slash_pos != NULL) {
        // Extract the directory path
        size_t dir_len = slash_pos - pattern;
        strncpy(dir_path, pattern, dir_len);
        dir_path[dir_len] = '\0';
        pattern = slash_pos + 1;
    }

    // Open the target directory for reading
    dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return;
    }

    // Iterate over directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip the entries "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Use custom fnmatch logic to match wildcard patterns
        if (my_fnmatch(pattern, entry->d_name) == 0) {
            char full_path[2048];
            snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
            
            t_token *new_token = malloc(sizeof(t_token));
            new_token->token = strdup(full_path);
            new_token->type = ARG;
            new_token->is_quote = 0;
            new_token->next = NULL;

            // Add the new token to the linked list
            if (!new_tokens) {
                new_tokens = new_token;
            } else {
                last_token->next = new_token;
            }
            last_token = new_token;
        }
    }

    closedir(dir);

    // If new tokens were found, replace the current token
    if (new_tokens) {
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
