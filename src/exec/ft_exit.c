/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/07/15 20:25:04 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_num_error(char *token, unsigned char exit_code);
static int	is_limit_error(int sign, char *str);

void	ft_exit(t_token *head)
{
	unsigned char	exit_code;

	exit_code = 0;
	// has args?
	if (!head)
		exit(0);
	// is n1 a num?
	exit_code = is_num_error(head->token, exit_code);
	if (!exit_code)
	{
		printf("exit_code:%i", exit_code);
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
	exit(exit_code);
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
	str = ft_strtrim(token, " ");
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
