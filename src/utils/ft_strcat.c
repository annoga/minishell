#include "../../inc/minishell.h"

char    *ft_strcat(char *dest, const char *src)
{
    char    *dest_ptr;
    
    dest_ptr = dest;
    while (*dest_ptr != '\0')
        dest_ptr++;
    while (*src != '\0')
    {
        *dest_ptr = *src;
        dest_ptr++;
        src++;
    }
    *dest_ptr = '\0';
    return (dest);
}