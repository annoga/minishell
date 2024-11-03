/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:44 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 16:43:06 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "struct.h"
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

// Apaños para mac
//# include <limits.h>
//# include <string.h>
# include <linux/limits.h>

//# include ".h"

extern int	g_mode;
extern int	debug;//This is a test variable and should be removed

/* TOKENIZER */
t_token	*tokenizer(char *line, t_env *env);
t_token	*get_token(char *line, int *i, t_env *env, int is_hdoc);
t_token	*handle_single_quote(char *line, int *i);
t_token	*handle_double_quote(char *line, int *i, t_env *env, int is_hdoc);
t_token	*handle_parenthesis(char *line, int *i);
t_token	*handle_space(char *line, int *i);
t_token	*handle_arg(char *line, int *i, int is_hdoc);
t_token	*handle_expansion(char *line, int *i);
t_token	*get_special_token(char *line, int *i);
t_token	*new_token(t_token_type type, char *value);
t_token	*create_token(char type, char *value, int *i);
t_token	*split_linker(char *line, t_env **env);
//void	print_list(t_token *head);
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

//void print_cmd(t_cmd *cmd, int level);


t_token *expansor(t_token *head, t_env **env, int is_hdoc, int is_quoted);
t_token *expansor_hdoc(t_token *head, t_env **env, int is_hdoc, int is_quoted);
void tokenize_env(t_token **tmp2, t_token **tmp, t_token **head, t_env **envp);
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
char *last_slash(char *prefix);


/* SYNTAX */
int	analize_tokens(t_token *token, t_env *env);
t_token_type	assing_type(char *token, t_synt *state);

int check_syntax(t_token *token);

/* EXECUTE */
void	command_analyzer(t_env **env, t_cmd *cmd);
int		free_env(t_env **envp);
char	*ft_getenv(char *key, t_env *envp);
char	**tenv_to_array(t_env *env);
int		ft_analyze_cmd(t_env **env, t_cmd *current);
int		get_heredocs(t_cmd *cmd, t_env **tenv, int internal);
char	*get_cmd_path(char *cmd, char *path_env);
int		is_command(char *path);
void	safe_pipe(t_pipe *fds);
pid_t	safe_fork(void);
int		safe_close(int fd);
int		safe_dup2(int old, int clone);
void	pipe_write_stdout(int *pipe);
void	pipe_read_stdin(int *pipe);
t_cmd	*process_command_block(t_cmd *cmd, int *err_code, t_env *tenv);
int		is_last_cmd_in_pipe(t_cmd *cmd, int pos);
void	update_pipes(t_pipe *fds, int j, t_cmd *next_cmd);
int		process_child(t_cmd *cmd, t_pipe *fds, t_env *tenv, int cmd_index);
int		wait_for_status(pid_t last_pid, int n);
int		redir_file_stdout(char *filename, int mode);
int		redir_file_stdin(char *filename, int mode);
int		redir_heredoc_stdin(int fd);
int		process_heredoc(t_file *current, t_env **tenv, int *status);
int		process_hdoc_child(char *word, t_pipe *fds, int expand, t_env **tenv);
int		clear_heredoc(t_file *target);

/* BUILTINS */
void	echo(t_cmd *head);
int		ft_exit(t_cmd *cmd, int verbose);
void	ft_env(t_env *env);
int     ft_cd(t_cmd *cmd, t_env *env);
void env_set_value(t_env **env, char *key, char *value);
t_env	*env_get_value(t_env *var, char *name);
void env_new(t_env **env, char *name, char *value);
void	ft_pwd(t_cmd *cmd);
int 	ft_unset(t_cmd *cmd, t_env **env);
int		ft_export(t_cmd *cmd, t_env **env);
void set_equal_value(t_env *env, char *str, int equal_pos);
int  ft_equal_position(char *str);
int not_valid_key(char *str);
void print_export(t_env *env);

/* UTILS */
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strstr(const char *str, const char *needle);
void	*return_error(char *str);
int		check_is_ok(char *line, t_env *env);
int ft_istoken(char c);
void	ft_soft_itoa(t_env **tmp, int n);
void	lst_add_back(void *lst, void *new);
void	lstclear(void *list, void (*del)(void *));
char	*free_split(char **split);
//char	*print_type(t_token_type type);
char	*free_tcmd(t_cmd **cmd_list);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	print_and_kill(char *str, int exit_status);


/* SIGNAL */
void handle_update_signal(t_signal *signals, enum e_signal_handle mode);



# endif
