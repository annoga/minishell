#include "../../inc/minishell.h"

DIR *open_directory(const char *dir_path)
{
    DIR *dir;
    dir = opendir(dir_path);
    if (!dir)
        perror("bash: ");
    return (dir);
}
static void add_matching_token(const char *entry_name, const char *pattern, t_token **new_tokens, t_token **last_token)
{
    t_token *new_token;

    if (ft_fnmatch(pattern, entry_name) == 0) 
    {
        new_token = create_token_from_entry(".", entry_name);
        if (new_token) 
        {
            if (!(*new_tokens))
                *new_tokens = new_token;
            else
                (*last_token)->next = new_token;
            *last_token = new_token;
        }
    }
}

static int is_valid_entry(const char *entry_name)
{
    if(ft_strncmp(entry_name, ".") != 0 && ft_strncmp(entry_name, "..") != 0)
        return 1;
    return 0;
}
void process_directory_entries(DIR *dir, const char *pattern, t_token **new_tokens, t_token **last_token)
{
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (is_valid_entry(entry->d_name))
            add_matching_token(entry->d_name, pattern, new_tokens, last_token);
    }
}




