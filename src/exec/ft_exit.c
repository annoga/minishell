/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:47:15 by anovoa            #+#    #+#             */
/*   Updated: 2024/07/14 16:35:10 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_token *head)
{
	unsigned char	exit_code;
	int				err;
	exit_code = 0;
	err = 0;
	// has args?
	if (!head)
		exit(0);
	// is n1 a num?
	if (!check_num(head->token, &err))
		print_exit_error(err)
		exit(2);
	if (!ft_isdigit(atoi(head->token)))
//	if (argc == 0)
		exit(exit_code);
/*	if (argc == 1)// && !isdigit(argv[0]))
		ft_atol();
	if (argc > 1)
		printf("Argument error");*/
//	if (argc == 1)//if under long
//		exit_code = atoi(argv[0]);
	exit(exit_code);
}

static int	check_num(char *token)
{
	int		i;
	int		has_num;
	int		sign;
	char	*str;

	i = 0;
	has_num = 0;
	sign = 1;
	str = ft_strtrim(token, " ");
	if (ft_issign(str[i]))
	{
		if (str[i++] == '-')
			sign = -1
	}
	limit_check(sign, str + i)//could have non digits
	while (str[i] && ft_isdigit(str[i++]))
		has_num = 1;
	if (has_num && !str[i])
		return (1);
	else
		return (0);
}

static int	limit_check(int sign, char *str, int *err)
{
	int	len;

	len = ft_strlen(str);
	if (len < 19)
		return (1);
	else if (len == 19)
	{
		if (sign == 1 && ft_strncmp((str), "9223372036854775807") > 0)
			return (2);
		if (sign == -1 && ft_strncmp((str), "9223372036854775808") > 0)
			return (2);
	}
	else if (len > 19)
		return (0);
}
