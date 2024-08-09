#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> // For read()
#include <sys/types.h>
#include <sys/stat.h>

int is_directory(const char *path) 
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int my_fnmatch(const char *pattern, const char *string)
{
    const char *patt = pattern, *s = string;

    while (*patt != '\0' && *s != '\0') {
        if (*patt == '*') {
            patt++;
            if (*patt == '\0') {
                return 0;  // Trailing '*' matches everything
            }
            while (*s != '\0') {
                if (my_fnmatch(patt, s) == 0) {
                    return 0;
                }
                s++;
            }
            return -1;
        } else if (*patt == *s) {
            patt++;
            s++;
        } else {
            return -1;
        }
    }

    if (*patt == '*') {
        patt++;
    }

    return (*patt == '\0' && *s == '\0') ? 0 : -1;
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
