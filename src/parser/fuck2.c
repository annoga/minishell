#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../inc/minishell.h"

// Function to normalize input by reducing multiple '*' to a single '*'
void normalize_input(char *input) {
    char *src = input;
    char *dst = input;

    while (*src != '\0') {
        *dst = *src;

        // If we encounter a '*', skip over any additional '*'
        if (*src == '*') {
            while (*(src + 1) == '*') {
                src++;
            }
        }

        src++;
        dst++;
    }
    *dst = '\0';  // Null-terminate the string
}

// Utility function to compare strings
int string_compare(const char *str1, const char *str2) {
    return ft_strcmp(str1, str2);
}

// Utility function to compare string prefix
int prefix_compare(const char *str, const char *prefix) {
    return ft_strncmp(str, prefix, ft_strlen(prefix));
}

// Utility function to compare string suffix
int suffix_compare(const char *str, const char *suffix) {
    size_t len_str = ft_strlen(str);
    size_t len_suffix = ft_strlen(suffix);

    if (len_str < len_suffix) {
        return 1;
    }

    return ft_strcmp(str + len_str - len_suffix, suffix);
}

// Utility function to check if the entry is a directory
int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

// Function to check if the entry matches the prefix and suffix criteria
int check_match(const char *name, const char *prefix, const char *suffix) {
    return (!prefix || prefix_compare(name, prefix) == 0) &&
           (!suffix || suffix_compare(name, suffix) == 0);
}

void handle_directory(const t_wilds *params);

// Function to process each directory entry
void process_entry(const char *path, struct dirent *entry, const t_wilds *params) {
    if (string_compare(entry->d_name, ".") == 0 || string_compare(entry->d_name, "..") == 0) {
        return;
    }

    if (check_match(entry->d_name, params->prefix, params->suffix)) {
        char *fullpath = construct_full_path(path, entry->d_name);
        if (fullpath) {
            printf("%s\n", fullpath);
            free(fullpath);
        }
    }

    if (params->depth > 0) {
        char *fullpath = construct_full_path(path, entry->d_name);
        if (fullpath && is_directory(fullpath)) {
            t_wilds new_params = {fullpath, params->prefix, params->suffix, params->depth - 1};
            handle_directory(&new_params);
        }
        free(fullpath);
    }
}

// Function to handle the directory listing and recursion
void handle_directory(const t_wilds *params) {
    struct dirent *entry;
    DIR *dp = opendir(params->path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        process_entry(params->path, entry, params);
    }

    closedir(dp);
}

// Function to process each directory entry
void handle_directory_entry(struct dirent *entry) {
    if (entry->d_type == DT_DIR && string_compare(entry->d_name, ".") != 0 && string_compare(entry->d_name, "..") != 0) {
        char *fullpath = construct_full_path(".", entry->d_name);
        if (fullpath) {
            printf("%s:\n", fullpath);
            t_wilds params = {fullpath, NULL, NULL, 0};
            handle_directory(&params);
            free(fullpath);
        }
    }
}

// Process special cases
void process_special_cases(char *input) {
    if (string_compare(input, "**/*") == 0 || string_compare(input, "***/*") == 0) {
        t_wilds params = {".", NULL, NULL, 1000};
        handle_directory(&params);
    }
}

// Process wildcard input
void process_wildcard_input(char *input) {
    char prefix[1024] = "";
    char suffix[1024] = "";
    char *star_pos = ft_strchr(input, '*');

    if (star_pos == input) {
        ft_strncpy(suffix, input + 1, sizeof(suffix) - 1);
    } else if (*(star_pos + 1) == '\0') {
        ft_strncpy(prefix, input, star_pos - input);
    } else {
        ft_strncpy(prefix, input, star_pos - input);
        ft_strncpy(suffix, star_pos + 1, sizeof(suffix) - 1);
    }

    t_wilds params = {".", prefix, suffix, 0};
    handle_directory(&params);
}

// List all directories
void list_all_directories() {
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        handle_directory_entry(entry);
    }

    closedir(dp);
}

// Process star slash input
void process_star_slash(char *input) {
    char path[1024];
    char *star_slash_pos = ft_strstr(input, "/*");
    size_t i = 0;

    while (input + i != star_slash_pos) {
        path[i] = input[i];
        i++;
    }
    path[i] = '\0';

    if (string_compare(path, "*") == 0) {
        list_all_directories();
    } else {
        t_wilds params = {path, NULL, NULL, 0};
        handle_directory(&params);
    }
}

// Handle input
void handle_input(char *input) {
    process_special_cases(input);

    normalize_input(input);

    if (string_compare(input, "*") == 0) {
        t_wilds params = {".", NULL, NULL, 0};
        handle_directory(&params);
    } else if (ft_strstr(input, "/*") != NULL) {
        process_star_slash(input);
    } else if (ft_strchr(input, '*')) {
        process_wildcard_input(input);
    } else {
        printf("Invalid input format. Use * for matching.\n");
    }
}

// Main function
int main() {
    char input[1024];

    printf("Enter your command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove newline character

    handle_input(input);

    return 0;
}
