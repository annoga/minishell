#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../inc/minishell.h"
//4

// char	*construct_full_path(const char *dir_path, const char *entry_name)
// {
// 	size_t base_len = strlen(dir_path);
//     size_t entry_len = strlen(entry_name);
//     char *full_path = (char *)malloc(base_len + entry_len + 2); // +2 for '/' and '\0'

//     if (full_path) {
//         strcpy(full_path, dir_path);
//         if (dir_path[base_len - 1] != '/') {
//             strcat(full_path, "/");
//         }
//         strcat(full_path, entry_name);
//     }

//     return full_path;
// }


// void set_params(t_wilds *params, const char *prefix, const char *suffix, int depth)
// {
//     params->prefix = prefix;
//     params->suffix = suffix;
//     params->depth = depth;
// }

// void normalize_input(char *input)
// {
//     char *src;
//     char *dst;

//     dst = input;
//     src = input;
//     while (*src != '\0') 
//     {
//         *dst = *src;
//         if (*src == '*') 
//         {
//             while (*(src + 1) == '*')
//                 src++;
//         }
//         src++;
//         dst++;
//     }
//     *dst = '\0';
// }

// int prefix_compare(const char *str, const char *prefix)
// {
//     return (ft_strncmp(str, prefix, ft_strlen(prefix)));
// }
// //3
// int suffix_compare(const char *str, const char *suffix)
// {
//     size_t len_str;
//     size_t len_suffix;

//     len_str = ft_strlen(str);
//     len_suffix = ft_strlen(suffix);
//     if (len_str < len_suffix)
//         return (1);
//     return (ft_strcmp(str + len_str - len_suffix, suffix));
// }

// int is_directory(const char *path)
// {
//     struct stat statbuf;

//     if (stat(path, &statbuf) != 0)
//         return (0);
//     return (S_ISDIR(statbuf.st_mode));
// }

// int check_match(const char *name, const char *prefix, const char *suffix)
// {
//     return ((!prefix || prefix_compare(name, prefix) == 0) &&
//            (!suffix || suffix_compare(name, suffix) == 0));
// }

// void append_token(t_token **token_list, char *str)
// {
//     t_token *token;
//     t_token *current;
//     char *clean_str;

//     if (strncmp(str, "./", 2) == 0)
//         clean_str = str + 2;
//     else
//         clean_str = str;

//     token = create_token(ARG, clean_str, 0);
//     if (*token_list == NULL)
//         *token_list = token;
//     else
//     {
//         current = *token_list;
//         while (current->next != NULL)
//             current = current->next;
//         current->next = token;
//     }
// }

// void handle_depth(const char *path, struct dirent *entry, const t_wilds *params, t_token **token_list)
// {
//     char *fullpath;
//     t_wilds new_params;

//     fullpath = construct_full_path(path, entry->d_name);
//     if (fullpath && is_directory(fullpath))
//     {
//         new_params.path = fullpath;
//         set_params(&new_params, params->prefix, params->suffix, params->depth - 1);
//         handle_directory(&new_params, token_list);
//     }
//     free(fullpath);
// }
//2
// void process_entry(const char *path, struct dirent *entry, const t_wilds *params, t_token **token_list)
// {
//     char *fullpath;

//     if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
//         return ;
//     if (check_match(entry->d_name, params->prefix, params->suffix)) 
//     {
//         fullpath = construct_full_path(path, entry->d_name);
//         if (fullpath)
//         {
//             append_token(token_list, fullpath);
//             free(fullpath);
//         }
//     }
//     if (params->depth > 0)
//         handle_depth(path, entry, params, token_list);
// }

// void handle_directory(const t_wilds *params, t_token **token_list)
// {
//     struct dirent *entry;
//     DIR *dp;
    
//     dp = opendir(params->path);
//     if (dp == NULL)
//     {
//         perror("opendir");
//         return ;
//     }
//     while ((entry = readdir(dp)) != NULL)
//         process_entry(params->path, entry, params, token_list);
//     closedir(dp);
// }

// void handle_directory_entry(struct dirent *entry, t_token **token_list)
// {
//     char *fullpath;
//     t_wilds params;

//     if (entry->d_type == DT_DIR && ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name, "..") != 0)
//     {
//         fullpath = construct_full_path(".", entry->d_name);
//         if (fullpath)
//         {
//             params.path = fullpath;
//             set_params(&params, NULL, NULL, 0);
//             handle_directory(&params, token_list);
//             free(fullpath);
//         }
//     }
// }



// void process_special_cases(char *input, t_token **token_list)
// {
//     t_wilds params;

//     if (ft_strcmp(input, "**/*") == 0 || ft_strcmp(input, "***/*") == 0)
//     {
//         params.path = ".";
//         set_params(&params, NULL, NULL, 1000);
//         handle_directory(&params, token_list);
//     }
// }
//1
// void process_star_slash(char *input, t_token **token_list)
// {
//     char path[1024];
//     char *star_slash_pos;
//     size_t i;
//     t_wilds params;
    
//     i = 0;
//     star_slash_pos = ft_strstr(input, "/*");
//     while (input + i != star_slash_pos)
//     {
//         path[i] = input[i];
//         i++;
//     }
//     path[i] = '\0';
//     if (ft_strcmp(path, "*") == 0)
//         list_all_directories(token_list);
//     else
//     {
//         params.path = path;
//         set_params(&params, NULL, NULL, 0);
//         handle_directory(&params, token_list);
//     }
// }

// void process_wildcard_input(char *input, t_token **token_list)
// {
//     char prefix[1024] = "";
//     char suffix[1024] = "";
//     char *star_pos;
//     t_wilds params;
    
//     star_pos = ft_strchr(input, '*');
//     if (star_pos == input)
//         ft_strncpy(suffix, input + 1, sizeof(suffix) - 1);
//     else if (*(star_pos + 1) == '\0')
//         ft_strncpy(prefix, input, star_pos - input);
//     else
//     {
//         ft_strncpy(prefix, input, star_pos - input);
//         ft_strncpy(suffix, star_pos + 1, sizeof(suffix) - 1);
//     }
//     params.path = ".";
//     set_params(&params, prefix, suffix, 0);
//     handle_directory(&params, token_list);
// }
// t_token	*allocate_token(void)
// {
// 	t_token	*new_token;

// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 	{
// 		perror("malloc");
// 		return (NULL);
// 	}
// 	new_token->next = NULL;
// 	return (new_token);
// }

// static t_token *create_space_token(void)
// {
//     t_token *space_token;

//     space_token = allocate_token();
//     if (!space_token)
//         return (NULL);
//     space_token->token = strdup(" ");
//     if (!space_token->token)
//     {
//         perror("strdup");
//         free(space_token);
//         return (NULL);
//     }
//     space_token->type = SPACE_TOKEN;
//     space_token->is_quote = 0;
//     return (space_token);
// }

// static void insert_space_tokens(t_token **tokens)
// {
//     t_token *current;
//     t_token *space_token;
//     t_token *next;

//     current = *tokens;
//     while (current->next)
//     {
//         next = current->next;
//         space_token = create_space_token();
//         if (!space_token)
//             return ;
//         current->next = space_token;
//         space_token->next = next;
//         current = next;
//     }
// }

// t_token *handle_input(char *input)
// {
//     t_token *token_list;
//     t_wilds params;
    
//     token_list = NULL;
//     process_special_cases(input, &token_list);
//     normalize_input(input);
//     if (ft_strcmp(input, "*") == 0)
//     {
//         params.path = ".";
//         set_params(&params, NULL, NULL, 0);
//         handle_directory(&params, &token_list);
//     }
//     else if (ft_strstr(input, "/*") != NULL)
//         process_star_slash(input, &token_list);
//     else if (ft_strchr(input, '*'))
//         process_wildcard_input(input, &token_list);
//     sort_alphabetic_token(token_list);
//     insert_space_tokens(&token_list);
//     return (token_list);
// }



// int main() {
//     char input[1024];

//     printf("Enter your command: ");
//     fgets(input, sizeof(input), stdin);
//     input[strcspn(input, "\n")] = '\0';  // Remove newline character

//     t_token *tokens = handle_input(input);
//     // Print the tokens for demonstration purposes
//     t_token *current = tokens;
//     while (current != NULL) {
//         printf("%s\n", current->token);
//         current = current->next;
//     }

//     // Free the tokens
//     while (tokens != NULL) {
//         t_token *next = tokens->next;
//         free(tokens->token);
//         free(tokens);
//         tokens = next;
//     }

//     return 0;
// }
