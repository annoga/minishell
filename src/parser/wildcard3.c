#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> // For read()
#include <sys/types.h>
#include <sys/stat.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

// Custom fgetc function to read a single character from stdin
int my_fgetc(FILE *stream) {
    char ch;
    if (read(fileno(stream), &ch, 1) == 1) {
        return (unsigned char) ch;
    } else {
        return EOF;
    }
}

// Custom fgets function to read input
char* my_fgets(char *str, int n, FILE *stream) {
    int ch, i = 0;

    // Read characters until end-of-file or newline
    while (i < n - 1 && (ch = my_fgetc(stream)) != EOF) {
        str[i++] = ch;
        if (ch == '\n')
            break;
    }
    str[i] = '\0';

    // Return NULL if no characters were read
    if (i == 0 && ch == EOF)
        return NULL;
    return str;
}

// Custom fnmatch function to match patterns
int my_fnmatch(const char *pattern, const char *string) 
{
    const char *p = pattern, *s = string;

    while (*p != '\0' && *s != '\0') {
        if (*p == '*') {
            p++;
            if (*p == '\0') {
                return 0;  // Trailing '*' matches everything
            }
            while (*s != '\0') {
                if (my_fnmatch(p, s) == 0) {
                    return 0;
                }
                s++;
            }
            return -1;
        } else if (*p == *s) {
            p++;
            s++;
        } else {
            return -1;
        }
    }

    if (*p == '*') {
        p++;
    }

    return (*p == '\0' && *s == '\0') ? 0 : -1;
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
