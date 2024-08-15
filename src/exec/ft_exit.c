/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/15 20:05:04 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_num_error(char *token, unsigned char exit_code);
static int	is_limit_error(int sign, char *str);

static int	has_one_arg(t_token *head);
static int	is_long(char *str);

/* Returns 1 if we have the following sequence of tokens:
 * ' ', 'arg1', ' ', 'arg2'
 * Otherwise, it returns 0.
 * */
static int	has_one_arg(t_token *head)//32
{
	t_token	*arg;

	arg = head->next;//arg1
	if (arg && arg->token)
		arg = arg->next;//32
		if (arg && arg->token)
			arg = arg->next;//arg2
			if (arg && arg->token)
				return (1);
	return (0);
}

/* Returns 1 if the given string can be read as a number
 * of type long.
 * Otherwise, it returns 0.
 * */
static int	is_long(char *str)
{
	return (0);
}

void	ft_exit(t_token *head)
{
	unsigned char	exit_code;

	exit_code = 0;
	// has args?
	if (!head)
		exit(0);
	// exit_code = read num?
	//
	if (has_one_arg(head))// one arg
	{
		if (is_long(head->next->token))// is long
		{
			//exit_code = (unsigned char)atol(head->next->token);
			//exit(exit_code);
			printf("exit_code: %s\n***\n", head->next->token);
		}
		else// not long
		{
			exit_code = 2;
			exit(2);
		}
	}
	else// multiple args
	{
		if (is_long(head->next->token))// arg 1 is long
		{
			//ToDo: Update $? to 1
			printf("exit: too many arguments");
			return ;
		}
		else// arg 1 !long
		{
			exit_code = 2;
			exit(exit_code);
		}
	}
//		printf("token: %s\n***\n", head->next->token);


	// is n1 a num?
	exit_code = is_num_error(head->token, exit_code);
//	printf("_exit_code: %i\n", exit_code);
	if (!exit_code)
	{
//		printf("exit_code:%i", exit_code);
		exit(exit_code);
	}
//		print_exit_error(err)
	if (!ft_isdigit(atoi(head->token)))
		exit(exit_code);
//	if (argc == 0)
/*	if (argc == 1)// && !isdigit(argv[0]))
		ft_atol();
	if (argc > 1)
		printf("Argument error");*/
//	if (argc == 1)//if under long
//		exit_code = atoi(argv[0]);
	exit(exit_code);//2 = numeric arg required//1 = too many args
}

static int	is_num_error(char *token, unsigned char exit_code)
{
	int		has_num;
	int		sign;
	char	*str;
	int		i;

	i = 0;
	has_num = 0;
	sign = 1;
	str = ft_strtrim(token, " ");//what happens if empty?
	if (ft_issign(str[i]))
		if (str[i++] == '-')
			sign = -1;
	exit_code = is_limit_error(sign, &str[i]);//could have non digits
	while (str[i] && ft_isdigit(str[i]))
	{
		has_num = 1;
		i++;
	}
	if (exit_code != 2 && has_num && !str[i])
		exit_code = 0;
	else
		exit_code = 2;
	free(str);
	return(exit_code);
}

static int	is_limit_error(int sign, char *str)
{
	int	len;

	if (!str)
		return (2);
	len = ft_strlen(str);
	if (len < 19)
		return (0);
	else if (len == 19)
	{
		if (sign == 1 && ft_strncmp((str), "9223372036854775807") > 0)
			return (2);
		if (sign == -1 && ft_strncmp((str), "9223372036854775808") > 0)
			return (2);
	}
	else if (len > 19)
		return (2);
	return (0);
}
