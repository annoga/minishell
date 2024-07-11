/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:44 by angeln            #+#    #+#             */
/*   Updated: 2024/07/11 11:32:53 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <stdio.h>
# include <unistd.h>
//# include ".h"

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
	ENV
}					t_token_type;

typedef struct s_token
{
	char			*token;
	int 			is_quote;
	// int 			and;
	// int 			or;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	int 			fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char			*key_name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* TOKENIZER */
t_token				*tokenizer(char *line);
t_token				*get_token(char *line, int *i);
t_token				*handle_single_quote(char *line, int *i);
t_token				*handle_double_quote(char *line, int *i);
t_token				*handle_parenthesis(char *line, int *i);
t_token				*handle_space(char *line, int *i);
t_token				*handle_arg(char *line, int *i);
t_token				*handle_dollar(char *line, int *i);
t_token				*get_special_token(char *line, int *i);
t_token				*new_token(t_token_type type, char *value, int is_quote);
t_token				*create_token(char type, char *value, int *i);
t_token				*split_linker(char *line);
void				print_list(t_token *head);
void				free_token(t_token *token);
void				add_token(t_token **head, t_token *new);

void    			add_top(t_token *head, t_token *new);
void    erase_one(t_token **head, t_token *to_erase);


/* PARSER */
t_token				*check_bonus_token(t_token *head);
t_token 			*assign_bonus_token(t_token *head, int type_bonus);

t_token *prueba_env(t_token *head);
void	ft_catch_env(char **envp, t_env **head);

// void check_builtin(t_token *head);
// void check_pipe_bonus(t_token *head);
// void check_redirect(t_token *head);
// void check_token(t_token *head);

/* EXECUTE */
t_token	*mock_builtin_tokenizer(t_token *head);//just for testing
void	echo(t_token *head);

/* UTILS */
char				*ft_strndup(const char *s, size_t n);
int					ft_strncmp(const char *s1, const char *s2);
void				*return_error(char *str);
int					check_is_ok(char *line);

#endif
