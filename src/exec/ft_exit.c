/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 13:34:03 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_one_arg(t_cmd *cmd);
static int	is_long(char *str);
static int	int_free(char **str, int status);
static int	print_err(char *arg, char *msg, int verbose);

/* Leaves minishell and sets errno to 0, 1 or 2 as appropriate.
 * If misused, it may not leave minishell, instead returning the relevant value
 * of errno.
 * */
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
	str = ft_strtrim(str, " ");
	if (ft_issign(str[i]))
		if (str[i++] == '-')
			sign = -1;
	len = ft_strlen(&str[i]);
	if (len > 19)
		return (0);
	else if (len == 19)
	{
		if (sign == 1 && ft_strcmp((str), "9223372036854775807") > 0)
			return (int_free(&str, 0));
		if (sign == -1 && ft_strcmp((str), "9223372036854775808") > 0)
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
