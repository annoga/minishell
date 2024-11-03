/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expansor_wildcard.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/08/13 20:32:34 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/08/13 20:32:34 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static void	process_wildcard_input(char *input, t_token **token_list)
{
	char	prefix[1024];
	char	suffix[1024];
	char	*star_pos;
	t_wilds	params;

	ft_bzero(prefix, sizeof(prefix));
	ft_bzero(suffix, sizeof(suffix));
	star_pos = ft_strchr(input, '*');
	if (star_pos == input)
		ft_strncpy(suffix, input + 1, sizeof(suffix) - 1);
	else if (*(star_pos + 1) == '\0')
		ft_strncpy(prefix, input, star_pos - input);
	else
	{
		ft_strncpy(prefix, input, star_pos - input);
		ft_strncpy(suffix, star_pos + 1, sizeof(suffix) - 1);
	}
	params.path = last_slash(prefix);
	set_params(&params, prefix, suffix, 0);
	handle_directory(&params, token_list);
	if (params.path)
		free((char *)params.path);
}

static void	process_star_slash(char *input, t_token **token_list)
{
	char	path[1024];
	char	*star_slash_pos;
	size_t	i;
	t_wilds	params;

	i = 0;
	star_slash_pos = ft_strstr(input, "/*");
	while (input + i != star_slash_pos)
	{
		path[i] = input[i];
		i++;
	}
	path[i] = '\0';
	if (ft_strcmp(path, "*") == 0)
		list_all_directories(token_list);
	else
	{
		params.path = path;
		set_params(&params, NULL, NULL, 0);
		handle_directory(&params, token_list);
	}
}

void	handle_directory(const t_wilds *params, t_token **token_list)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(params->path);
	if (dp == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dp);
	while (entry != NULL)
	{
		process_entry(params->path, entry, params, token_list);
		entry = readdir(dp);
	}
	closedir(dp);
}

static void	process_special_cases(char *input, t_token **token_list)
{
	t_wilds	params;

	if (ft_strcmp(input, "**/*") == 0 || ft_strcmp(input, "***/*") == 0)
	{
		params.path = ".";
		set_params(&params, NULL, NULL, 1000);
		handle_directory(&params, token_list);
	}
}

t_token	*handle_input(char *input)
{
	t_token	*token_list;
	t_wilds	params;

	token_list = NULL;
	process_special_cases(input, &token_list);
	normalize_input(input);
	if (ft_strcmp(input, "*") == 0)
	{
		params.path = ".";
		set_params(&params, NULL, NULL, 0);
		handle_directory(&params, &token_list);
	}
	else if (ft_strstr(input, "/*") != NULL)
		process_star_slash(input, &token_list);
	else if (ft_strchr(input, '*'))
		process_wildcard_input(input, &token_list);
	sort_alphabetic_token(token_list);
	insert_space_tokens(&token_list);
	return (token_list);
}
