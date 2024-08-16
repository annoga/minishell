/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:51:07 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/16 20:37:22 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Prints environment variables. Returns 0 if executed correctly, 125 if any
 * option is passed, or 127 for any other argument */
int	ft_env(t_token *head, t_env *env)
{
	if (head && head->next)
	{
		if (head->next->token[0] == '-')
		{
			ft_putendl_fd("env: invalid option", 2);
			return (125);
		}
		ft_putendl_fd("env: No such file or directory", 2);
		return (127);
	}
	while (env->next)
	{
		printf("%s=%s\n", env->key_name, env->value);
		env = env->next;
	}
	return (0);
}
