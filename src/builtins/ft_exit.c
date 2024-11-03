/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 21:13:28 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_one_arg(t_cmd *cmd);
static int	is_long(char *str);
static int	print_err(char *arg, char *msg, int verbose);

int	ft_exit(t_cmd *cmd, int verbose)
{
	if (!cmd->cmd[1] && print_err(NULL, NULL, verbose))
		exit(0);
	if (has_one_arg(cmd))
	{
		if (is_long(cmd->cmd[1]) && print_err(NULL, NULL, verbose))
			exit((unsigned char)ft_atol(cmd->cmd[1]));
		else if (print_err(cmd->cmd[1], "numeric argument required", verbose))
			exit(2);
	}
	else
	{
		if (is_long(cmd->cmd[1]))
		{
			print_err(NULL, "too many arguments", verbose);
			return (1);
		}
		else if (print_err(cmd->cmd[1], "numeric argument required", verbose))
			exit(2);
	}
	return (1);
}

/* Returns 0 if we have the following sequence of tokens:
 * ' ', 'arg1', ' ', 'arg2'
 * Otherwise, it returns 1.
 * */
static int	has_one_arg(t_cmd *cmd)
{
	if (cmd->cmd[1] != NULL && cmd->cmd[2] == NULL)
		return (1);
	else
		return (0);
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
	printf("%s\n", str);
	if (ft_issign(str[i]))
		if (str[i++] == '-')
			sign = -1;
	len = ft_strlen(&str[i]);
	if (len > 19)
		return (0);
	else if (len == 19)
	{
		if (sign == 1 && ft_strcmp((str), "9223372036854775807") > 0)
			return (0);
		if (sign == -1 && ft_strcmp((str), "9223372036854775808") > 0)
			return (0);
	}
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	print_err(char *arg, char *msg, int verbose)
{
	if (verbose)
		ft_putendl_fd("exit", 2);
	if (msg)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		if (arg)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(msg, 2);
	}
	return (1);
}
