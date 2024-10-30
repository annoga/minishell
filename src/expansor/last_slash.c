#include "../../inc/minishell.h"

char *last_slash(char *prefix)
{
    char *last_slash;
    char *path;
    size_t path_len;

    last_slash = ft_strrchr(prefix, '/');
    if (!last_slash)
        return (ft_strdup("."));
    path_len = last_slash - prefix;
    path = malloc(path_len + 1);
    if (!path)
        return (NULL);
    ft_strncpy(path, prefix, path_len);
    path[path_len] = '\0';
    ft_memmove(prefix, (last_slash + 1), (ft_strlen(last_slash + 1) + 1));
    return (path);
}