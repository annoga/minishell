/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:52:44 by angeln            #+#    #+#             */
/*   Updated: 2024/05/23 18:54:27 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include "readline/readline.h"
# include "../libft/libft.h"
# include "readline/history.h"
//# include ".h"
typedef struct s_token
{
    char            *token;
    int             is_builtin;
    int             is_pipe;
    int             is_redir;
    int             is_bonus;
    int             is_arg;
    struct s_token  *next;
} t_token;

int	ft_strncmp(const char *s1, const char *s2);
char	*skip_to_next_word(char *line);
char	*skip_separator(char *line);
int skip_redir_bonus(char c1, char *line);
void check_builtin(t_token *head);
void check_pipe_bonus(t_token *head);
void check_redirect(t_token *head);
void check_token(t_token *head);
char	**split_line(char *line, char *(*skip)(char *), char *(*next)(char *));
t_token	*ft_lstnew(char *content);

#endif