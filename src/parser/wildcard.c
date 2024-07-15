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
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        // Construct the full path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, dp->d_name);

        // Check if the entry matches the pattern
        if (match_pattern(pattern, dp->d_name)) {
            printf("%s\n", full_path);
        }

        // Check if the entry is a directory and recursively search it
        if (is_directory(full_path)) {
            search_directory(full_path, pattern);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *directory = argv[1];
    const char *pattern = argv[2];

    search_directory(directory, pattern);

    return 0;
}