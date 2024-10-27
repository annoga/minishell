/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:50:17 by angeln            #+#    #+#             */
/*   Updated: 2024/10/27 20:51:05 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_from_envpath(char *cmd, char *path_env);
static char	*ft_pathjoin(char const *path, char const *file);

/* This function will attempt to find a valid path to the given command,
 * mimicking bash behaviour:
 * 1) If the command contains a '/', it will be returned as is, if it 
 * exists, or NULL otherwise.
 * 2) If a path exists that is contained in the PATH environment variable,
 * it will be returned, or NULL otherwise.
 * 3) If the PATH environment variable does not exist, but the command 
 * points to an existing file, it will be returned, NULL otherwise.
 * */
//if '/', check if it exists, and return it.
//else, split path
char	*get_cmd_path(char *cmd, char *path_env)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (path_env)
		return (get_from_envpath(cmd, path_env));
	else if (!path_env)
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
	return (NULL);
}

static char	*get_from_envpath(char *cmd, char *path_env)
{
	char	**folders;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	folders = ft_split(path_env, ':');
	if (!folders)
		return (NULL);
	while (folders[i])
	{
		path = ft_pathjoin(folders[i], cmd);
		if (!path)
			return (free_split(folders));
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
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
