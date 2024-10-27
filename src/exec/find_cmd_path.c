/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:50:17 by angeln            #+#    #+#             */
/*   Updated: 2024/10/26 15:47:07 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_pathjoin(char const *path, char const *file);

/* This function will iterate the PATH element in env variable in order to find
 * one that can be executed */
char	*find_cmd_path(char *cmd, char *path_env)
{
	char	**folders;
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	folders = NULL;//
//	printf("here split:%p\n", path_env);
//	return (NULL);
	if (path_env)//
	{//
	folders = ft_split(path_env, ':');
	if (!folders)
		return (NULL);
	while (folders[i])
	{
		path = ft_pathjoin(folders[i], cmd);
		if (!path)
			return (free_split(folders));
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	}//
	if (!path && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		path = ft_strdup(cmd);
	if (folders)//
		free_split(folders);
	return (path);
}

static char	*ft_pathjoin(char const *path, char const *file)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(path) + ft_strlen(file) + 2);
	if (!result)
		return (NULL);
	while (path && path[i])
	{
		result[i] = path[i];
		i++;
	}
	result[i++] = '/';
	while (file && file[j])
	{
		result[i + j] = file[j];
		j++;
	}
	result[i + j] = 0;
	return (result);
}
