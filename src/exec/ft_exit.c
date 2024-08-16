/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/16 18:16:23 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_one_arg(t_token *head);
static int	is_long(char *str);
static int	int_free(char **str, int status);

/* ToDo: Print "exit" when it fits (at least after success) */
// ToDo print through fd 2!!
void	ft_exit(t_token *head)
{
	if ((!head || !head->next) && printf("exit\n"))
		exit(0);
	if (has_one_arg(head))
	{
		if (is_long(head->next->token) && printf("exit\n"))
			exit((unsigned char)ft_atol(head->next->token));
		else if (printf("exit\nexit: numeric argument required\n"))
			exit(2);
	}
	else
	{
		if (is_long(head->next->token))
		{
			//ToDo: Update $? to 1, possibly via return
			printf("exit\nexit: too many arguments\n");
			return ;
		}
		else if (printf("exit\nexit: numeric argument required\n"))
			exit(2);
	}
	return ;
}

/* Returns 0 if we have the following sequence of tokens:
 * ' ', 'arg1', ' ', 'arg2'
 * Otherwise, it returns 1.
 * */
static int	has_one_arg(t_token *head)
{
	t_token	*arg;

	arg = head->next;
	if (arg && arg->token)
	{
		arg = arg->next;
		if (arg && arg->token)
		{
			arg = arg->next;
			if (arg && arg->token)
				return (0);
		}
	}
	return (1);
}

/* Returns 1 if the given string can be read as a number of type long.
 * Otherwise, it returns 0.
 * */
static int	is_long(char *str)
{
	int	len;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	str = ft_strtrim(str, " ");
	if (ft_issign(str[i]))
		if (str[i++] == '-')
			sign = -1;
	len = ft_strlen(&str[i]);
	if (len > 19)
		return (0);
	else if (len == 19)
	{
		if (sign == 1 && ft_strncmp((str), "9223372036854775807") > 0)
			return (int_free(&str, 0));
		if (sign == -1 && ft_strncmp((str), "9223372036854775808") > 0)
			return (int_free(&str, 0));
	}
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (int_free(&str, 0));
	return (int_free(&str, 1));
}

/* Frees and returns the appropriate status */
static int	int_free(char **str, int status)
{
	free(*str);
	*str = NULL;
	return (status);
}
