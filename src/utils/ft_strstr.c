#include "../../inc/minishell.h"

char *ft_strstr(const char *str, const char *needle)
{
    size_t i;
    size_t j;

    if (needle[0] == '\0')
        return (char *)str;
    i = 0;
    while (str[i])
    {
        j = 0; // Reset j for each new position in str
        while (str[i + j] == needle[j]) {
            if (needle[j] == '\0') {
                return (char *)(str + i);
            }
            j++;
        }
        i++;
    }
    return NULL;
}
