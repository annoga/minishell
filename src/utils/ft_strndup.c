/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:52:02 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/30 21:52:16 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, (char *)s, n + 1);
	return (dup);
}


// void check_token(t_token *head)
// {
//     check_builtin(head);
//     check_pipe_bonus(head);
//     check_redirect(head);
//     if(!head->is_builtin && !head->is_pipe && !head->is_redir
//	&& !head->is_bonus)
//         head->is_arg = 1;
//     else
//         head->is_arg = 0;
// }
// void check_pipe_bonus(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, "|"))
//     {
//         head->is_pipe = 1;
//         head->is_bonus = 0;
//     }
//     else if(!ft_strncmp(tmp->token, "||") || !ft_strncmp(tmp->token, "&&"))
//     {
//         head->is_pipe = 0;
//         head->is_bonus = 1;
//     }
//     else
//     {
//         head->is_pipe = 0;
//         head->is_bonus = 0;
//     }
// }

// void check_redirect(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, ">") || !ft_strncmp(tmp->token, ">>") ||
//         !ft_strncmp(tmp->token, "<") || !ft_strncmp(tmp->token, "<<"))
//         head->is_redir = 1;
//     else
//         head->is_redir = 0;
// }

// void check_builtin(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, "echo") || !ft_strncmp(tmp->token, "cd") ||
//         !ft_strncmp(tmp->token, "pwd") || !ft_strncmp(tmp->token, "export")
//	||
//         !ft_strncmp(tmp->token, "unset") || !ft_strncmp(tmp->token, "env") ||
//         !ft_strncmp(tmp->token, "exit"))
//         head->is_builtin = 1;
//     else
//         head->is_builtin = 0;
// }
