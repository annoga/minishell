/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/15 23:26:20 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_one_arg(t_token *head);
static int	is_long(char *str);
static int	int_free(char **str, int status);

/* Returns 0 if we have the following sequence of tokens:
 * ' ', 'arg1', ' ', 'arg2'
 * Otherwise, it returns 1.
 * */
static int	has_one_arg(t_token *head)//32
{
	t_token	*arg;

	arg = head->next;//arg1
	if (arg && arg->token)
	{
		arg = arg->next;//32
		if (arg && arg->token)
		{
			arg = arg->next;//arg2
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

	//trim
	//sign
	//too long? return 0
	//any nondigit? return 0
	//return 1
	i = 0;
	sign = 1;
	str = ft_strtrim(str, " ");//what happens if empty?
	if (ft_issign(str[i]))
		if (str[i++] == '-')
			sign = -1;
	len = ft_strlen(&str[i]);//length without sign, if any
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

static int	int_free(char **str, int status)
{
	free(*str);
	*str = NULL;
	return (status);
}

/* ToDo: Print "exit" when it fits (at least after success) */
void	ft_exit(t_token *head)
{
	unsigned char	exit_code;

	exit_code = 0;
	// has args?
	if (!head)
		exit(0);
	// exit_code = read num?
	//
	if (has_one_arg(head))
	{
		if (is_long(head->next->token))
		{
			exit_code = (unsigned char)ft_atol(head->next->token);
			exit(exit_code);
		}
		else
		{
			printf("exit: numeric argument required\n");// ToDo print via fd 2!!
			exit_code = 2;
			exit(2);
		}
	}
	else// multiple args
	{
		if (is_long(head->next->token))
		{
			//ToDo: Update $? to 1, possibly via return
			printf("exit: too many arguments\n");// ToDo print through fd 2!!
			return ;
		}
		else// arg 1 !long
		{
			printf("exit: numeric argument required\n");// ToDo print via fd 2!!
			exit_code = 2;
			exit(exit_code);
		}
	}
	return ;
}
