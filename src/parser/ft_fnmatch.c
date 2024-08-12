#include "../../inc/minishell.h"

int finalize_match(const char *patt, const char *s)
{
    if (*patt == '*')
        patt++;
    if(*patt == '\0' && *s == '\0')
        return (0);
    else
        return (-1);
}

int match_pattern(const char *patt, const char *s)
{
    while (*patt != '\0' && *s != '\0')
    {
        if (*patt == '*')
            return (handle_asterisk(patt, s));
        else if (*patt == *s)
        {
            patt++;
            s++;
        } 
        else
            return (-1);
    }
    return (finalize_match(patt, s));
}

int handle_asterisk(const char *patt, const char *s)
{
    patt++;
    if (*patt == '\0')
        return (0);
    while (*s != '\0') 
    {
        if (match_pattern(patt, s) == 0)
            return (0);
        s++;
    }
    return (-1);
}

int ft_fnmatch(const char *pattern, const char *string)
{
    return (match_pattern(pattern, string));
}
// int main() {
//     char pattern[256];

//     // Prompt user for input pattern
//     printf("Enter the file/folder pattern (use '*' for wildcard): ");
//     if (my_fgets(pattern, sizeof(pattern), stdin) != NULL) {
//         // Remove newline character from the input
//         pattern[strcspn(pattern, "\n")] = '\0';

//         // List files and directories matching the pattern
//         listFiles(pattern);
//     } else {
//         printf("Failed to read input.\n");
//     }

//     return 0;
// }
