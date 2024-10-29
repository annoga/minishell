/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:51:07 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/30 00:09:05 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Prints environment variables. Ignores options and arguments.
 * Always returns 0 */
void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key_name, env->value);
		env = env->next;
	}
	exit(0);
}
