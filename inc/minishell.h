/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:44 by angeln            #+#    #+#             */
/*   Updated: 2024/08/19 20:37:42 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>

// Apaños para mac
//# include <limits.h>
//# include <string.h>
# include <linux/limits.h>

//# include ".h"

extern int	debug;//This is a test variable and should be removed

typedef enum e_token_type
{
	ARG,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	BUILTIN,
	AND,
	OR,
	L_PAREN,
	R_PAREN,
	SPACE_TOKEN,
	EXIT_STATUS,
	ENV
}					t_token_type;

typedef struct s_token
{
	char			*token;
	int				is_quote;
	// int 			and;
	// int 			or;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char			*key_name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_wilds
{
    const char *path;
    const char *prefix;
    const char *suffix;
    int depth;
}	t_wilds;


/* TOKENIZER */
t_token	*tokenizer(char *line);
t_token	*get_token(char *line, int *i);
t_token	*handle_single_quote(char *line, int *i);
t_token	*handle_double_quote(char *line, int *i);
t_token	*handle_parenthesis(char *line, int *i);
t_token	*handle_space(char *line, int *i);
t_token	*handle_arg(char *line, int *i);
t_token	*handle_expansion(char *line, int *i);
t_token	*get_special_token(char *line, int *i);
t_token	*new_token(t_token_type type, char *value, int is_quote);
t_token	*create_token(char type, char *value, int *i);
t_token	*split_linker(char *line, t_env **env);
void	print_list(t_token *head);
void	free_token(t_token **token);
void	add_token(t_token **head, t_token *new);

void	add_top(t_token *head, t_token *new);
void	erase_one(t_token **head, t_token *to_erase);

/* PARSER */
t_token	*check_bonus_token(t_token *head);
t_token	*assign_bonus_token(t_token *head, int type_bonus);

t_token *expansor(t_token *head);
void	ft_catch_env(char **envp, t_env **head);

// void check_builtin(t_token *head);
// void check_pipe_bonus(t_token *head);
// void check_redirect(t_token *head);
// void check_token(t_token *head);

/* WILDCARD */
void sort_alphabetic_token(t_token *head);
t_token *handle_input(char *input);
void set_params(t_wilds *params, const char *prefix, const char *suffix, int depth);
void insert_space_tokens(t_token **tokens);
void list_all_directories(t_token **token_list);
void normalize_input(char *input);
void handle_directory(const t_wilds *params, t_token **token_list);
void process_entry(const char *path, struct dirent *entry, const t_wilds *params, t_token **token_list);
char	*construct_full_path(const char *dir_path, const char *entry_name);
int prefix_compare(const char *str, const char *prefix);
int suffix_compare(const char *str, const char *suffix);
int is_directory(const char *path);


/* EXECUTE */
t_token	*mock_builtin_tokenizer(t_token *head, t_env **env);//just for testing
void	echo(t_token *head);
void	ft_exit(t_token *head);
int		ft_env(t_token *head, t_env *env);//maybe should return unsigned char
int		free_env(t_env **envp);

/* UTILS */
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strstr(const char *str, const char *needle);
void	*return_error(char *str);
int		check_is_ok(char *line);
int ft_istoken(char c);

#endif
