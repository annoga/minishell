/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:44 by angeln            #+#    #+#             */
/*   Updated: 2024/10/21 13:19:24 by angeln           ###   ########.fr       */
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
# include <limits.h>
# include <string.h>
//# include <linux/limits.h>

//# include ".h"

extern int	debug;//This is a test variable and should be removed

typedef enum e_token_type
{
	NO_TYPE = 0,
	AND,
	OR,
	PIPE,
	L_PAREN,
	R_PAREN,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	COMMAND,
	ARG,
	SPACE_TOKEN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	FILES,
	EXIT_STATUS,
	ENV
}					t_token_type;

typedef struct s_token
{
	char			*token;
	int				is_quote;
	t_token_type	type;
	t_token_type	syntaxis;
	struct s_token	*next;
}					t_token;

	typedef struct s_file
	{
		char			*name;
		t_token_type	type;
		struct s_file	*next;
	}					t_file;

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


typedef struct s_synt
{
	t_token_type	last_token_type;
	int				parenthesis_balance;
	int				is_cmd_assigned;
	int				expecting_cmd;
	int				has_content;
}	t_synt;

typedef struct s_cmd
{
	char			**cmd;
	t_file			*files;
	t_token_type	connection_type; //AND, OR, PIPE
	int 			parenthesis;
	struct s_cmd	*subcommand;
	struct s_cmd	*next;
}	t_cmd;





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
t_token	*new_token(t_token_type type, char *value);
t_token	*create_token(char type, char *value, int *i);
t_token	*split_linker(char *line, t_env **env);
void	print_list(t_token *head);
void	free_token(t_token **token);
void	add_token(t_token **head, t_token *new);

void	add_top(t_token *head, t_token *new);
void	erase_one(t_token **head, t_token *to_erase);

/* PARSER */
t_cmd	*parser(t_token *token);
void	*add_dir(void *array, void *dir);
//void	free_split(char **split);
int		ft_arraylen(void *array);
void	del_command(void *command);
void	lstclear(void *list, void (*del)(void *));
void	set_subcommand(t_cmd **cmd, t_token **tkn_p);
t_cmd	*add_command(t_cmd **cmd_lst);
void	set_file(t_cmd **cmd, t_token **token);
void	lst_add_back(void *lst, void *new);
t_cmd	*add_command(t_cmd **cmd_lst);

void print_cmd(t_cmd *cmd, int level);


t_token *expansor(t_token *head);
void	ft_catch_env(char **envp, t_env **head);
int ft_issafedup(t_env **tmp, char *name, char *value);
void ft_empty_env(t_env **tmp);


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

/* SYNTAX */
int	analize_tokens(t_token *token);
t_token_type	assing_type(char *token, t_synt *state);

int check_syntax(t_token *token);

/* EXECUTE */
t_token	*mock_builtin_tokenizer(t_token *head, t_env **env);//just for testing
void	echo(t_token *head);
void	ft_exit(t_token *head);
int		ft_env(t_token *head, t_env *env);//maybe should return unsigned char
int		free_env(t_env **envp);
char	*ft_getenv(char *key, t_env *envp);
char	**ft_get_env_array(t_env *env);
int		ft_analyze_cmd(t_token *head, t_env *env);
char	*find_cmd_path(char *cmd, char *path_env);
int		is_command(char *path);

/* UTILS */
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strstr(const char *str, const char *needle);
void	*return_error(char *str);
int		check_is_ok(char *line);
int ft_istoken(char c);
void	ft_soft_itoa(t_env **tmp, int n);
void	lst_add_back(void *lst, void *new);
void	lstclear(void *list, void (*del)(void *));
char	*free_split(char **split);
char	*print_type(t_token_type type);


#endif
