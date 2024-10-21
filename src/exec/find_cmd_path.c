/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:50:17 by angeln            #+#    #+#             */
/*   Updated: 2024/10/17 18:19:54 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function will iterate the PATH element in env variable in order to find
 * one that can be executed */
char	*find_cmd_path(char *path, char **env)
{
	//if given path F_OK and X_OK, lo dejamos//ver si prio antes o después de PATH
	//while elementos en PATH:
	if (access(path, F_OK) == 0)
		return (NULL);
	else
		return (NULL);
	if (env)
		return (NULL);
	return (NULL);
}
