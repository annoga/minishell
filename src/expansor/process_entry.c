/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:19:34 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:19:35 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_match(const char *name, const char *prefix,
			const char *suffix)
{
	return ((!prefix || prefix_compare(name, prefix) == 0)
		&& (!suffix || suffix_compare(name, suffix) == 0));
}

static void	append_token(t_token **token_list, char *str)
{
	t_token	*token;
	t_token	*current;
	char	*clean_str;

	clean_str = str;
	while (ft_strncmp(clean_str, "../", 3) == 0)
		clean_str += 3;
	if (ft_strncmp(str, "./", 2) == 0)
		clean_str += 2;
	token = create_token(ARG, clean_str, 0);
	if (*token_list == NULL)
		*token_list = token;
	else
	{
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = token;
	}
}

char	*construct_full_path(const char *dir_path, const char *entry_name)
{
	size_t	base_len;
	size_t	entry_len;
	char	*full_path;

	base_len = ft_strlen(dir_path);
	entry_len = ft_strlen(entry_name);
	full_path = (char *)malloc(base_len + entry_len + 2);
	if (full_path)
	{
		ft_strlcpy(full_path, dir_path, ft_strlen(dir_path) + 1);
		if (dir_path[base_len - 1] != '/')
			ft_strcat(full_path, "/");
		ft_strcat(full_path, entry_name);
	}
	return (full_path);
}

static void	handle_depth(const char *path, struct dirent *entry,
				const t_wilds *params, t_token **token_list)
{
	char	*fullpath;
	t_wilds	new_params;

	fullpath = construct_full_path(path, entry->d_name);
	if (fullpath && is_directory(fullpath))
	{
		new_params.path = fullpath;
		set_params(&new_params, params->prefix, params->suffix,
			params->depth - 1);
		handle_directory(&new_params, token_list);
	}
	free(fullpath);
}

void	process_entry(const char *path, struct dirent *entry,
		const t_wilds *params, t_token **token_list)
{
	char	*fullpath;

	if (ft_strcmp(entry->d_name, ".") == 0
		|| ft_strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.')
		return ;
	if (check_match(entry->d_name, params->prefix, params->suffix))
	{
		fullpath = construct_full_path(path, entry->d_name);
		if (fullpath)
		{
			append_token(token_list, fullpath);
			free(fullpath);
		}
	}
	if (params->depth > 0)
		handle_depth(path, entry, params, token_list);
}
