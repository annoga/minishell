#include "../../inc/minishell.h"

// Function to check if the name matches the pattern with '*'
int matchPattern(const char *pattern, const char *name) {
    if (*pattern == '\0') {
        return *name == '\0';
    }

    if (*pattern == '*') {
        while (*pattern == '*') {
            pattern++;
        }

        if (*pattern == '\0') {
            return 1;
        }

        while (*name != '\0') {
            if (matchPattern(pattern, name)) {
                return 1;
            }
            name++;
        }

        return 0;
    } else {
        if (*pattern == *name || *pattern == '?') {
            return matchPattern(pattern + 1, name + 1);
        } else {
            return 0;
        }
    }
}

// Function to list files and directories matching the pattern
void listFiles(const char *pattern) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (matchPattern(pattern, entry->d_name)) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

// Custom implementation of fgetc using read
int getchr() {
    char c;
    return (read(STDIN_FILENO, &c, 1) == 1) ? (unsigned char)c : EOF;
}

// Function to read input from the user
void readInput(char *buffer, int size) {
    int i = 0;
    int c;
    while (i < size - 1 && (c = getchr()) != '\n' && c != EOF) {
        buffer[i++] = (char)c;
    }
    buffer[i] = '\0';
}

int main() {
    char pattern[256];

    printf("Enter the file/folder pattern (use '*' for wildcard): ");
    readInput(pattern, sizeof(pattern));

    listFiles(pattern);

    return 0;
}