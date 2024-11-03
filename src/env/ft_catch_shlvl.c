/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catch_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:56:56 by crmanzan          #+#    #+#             */
/*   Updated: 2024/11/03 19:57:05 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_catch_shlvl(t_env **tmp, int *shlvl_flag)
{
	int	shlvl;

	shlvl = 0;
	if ((*tmp)->key_name && ft_strcmp((*tmp)->key_name, "SHLVL\0") == 0)
	{
		shlvl = ft_atoi((*tmp)->value);
		if (shlvl > 999)
		{
			ft_putstr_fd("minishell: shell level (", 2);
			free((*tmp)->value);
			ft_soft_itoa(tmp, shlvl + 1);
			ft_putstr_fd((*tmp)->value, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			shlvl = 1;
		}
		else if (shlvl < 999 && shlvl >= 0)
			shlvl++;
		else
			shlvl = 0;
		free((*tmp)->value);
		ft_soft_itoa(tmp, shlvl);
		*shlvl_flag = 1;
	}
}
