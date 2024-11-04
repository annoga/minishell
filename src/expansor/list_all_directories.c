/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_all_directories.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:16:28 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:16:29 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_directory_entry(struct dirent *entry, t_token **token_list)
{
	char	*fullpath;
	t_wilds	params;

	if (entry->d_type == DT_DIR && ft_strcmp(entry->d_name, ".") != 0
		&& ft_strcmp(entry->d_name, "..") != 0 && entry->d_name[0] != '.')
	{
		fullpath = construct_full_path(".", entry->d_name);
		if (fullpath)
		{
			params.path = fullpath;
			set_params(&params, NULL, NULL, 0);
			handle_directory(&params, token_list);
			free(fullpath);
		}
	}
}

void	list_all_directories(t_token **token_list)
{
	DIR				*dp;
	struct dirent	*entry;

	dp = opendir(".");
	if (dp == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dp);
	while (entry != NULL)
	{
		handle_directory_entry(entry, token_list);
		entry = readdir(dp);
	}
	closedir(dp);
}
