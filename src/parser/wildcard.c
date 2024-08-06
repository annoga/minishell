#include "../../inc/minishell.h"
int match_pattern(const char *pattern, const char *string) {
    const char *p = pattern;
    const char *s = string;
    const char *star = NULL;
    const char *ss = s;

    while (*s) {
        if (*p == '*') {
            star = p++;
            ss = s;
        } else if (*p == *s || *p == '?') {
            p++;
            s++;
        } else if (star) {
            p = star + 1;
            s = ++ss;
        } else {
            return 0;
        }
    }

    while (*p == '*') {
        p++;
    }

    return !*p;
}

int is_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    } else {
        return 0;
    }
}

void search_directory(const char *base_path, const char *pattern) {
    struct dirent *dp;
    DIR *dir = opendir(base_path);

    // Unable to open directory stream
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        printf(":%s)\n", dp->d_name);
        if (ft_strncmp(dp->d_name, ".") == 0 || ft_strncmp(dp->d_name, "..") == 0)
            continue;

        // Construct the full path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, dp->d_name);
        // Skip directories
        if (is_directory(full_path)) {
            continue;
        }

        // Check if the entry matches the pattern
        if (match_pattern(pattern, dp->d_name)) {
            printf("%c\n", dp->d_type);
            printf("%s\n", full_path);
        }
    }

    closedir(dir);
}

void parse_path_and_pattern(const char *input, char *directory, char *pattern) {
    const char *last_slash = strrchr(input, '/');
    if (last_slash) {
        size_t dir_len = last_slash - input;
        strncpy(directory, input, dir_len);
        directory[dir_len] = '\0';
        strcpy(pattern, last_slash + 1);
    } else {
        strcpy(directory, ".");
        strcpy(pattern, input);
    }
}

// int main(int argc, char *argv[]) {
//     // if (argc != 2) {
//     //     fprintf(stderr, "Usage: %s <directory/pattern>\n", argv[0]);
//     //     exit(EXIT_FAILURE);
//     // }
//     (void)argc;
//     char directory[1024];
//     char pattern[1024];

//     parse_path_and_pattern(argv[1], directory, pattern);

//     search_directory(directory, pattern);

//     return 0;
// }