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

static char	*construct_full_path(const char *dir_path, const char *entry_name)
{
	char	*full_path;

	(void)dir_path;
	full_path = malloc(2048);
	if (!full_path)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strlcpy(full_path, dir_path, PATH_MAX);
	ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, (char *)entry_name, PATH_MAX);
	return (full_path);
}

t_token	*allocate_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc");
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

static int	initialize_token(t_token *token, char *full_path, const char *dir_path, const char *entry_name)
{
	char *token_value;

	if (strcmp(dir_path, ".") == 0)
        token_value = strdup(entry_name);
    else
	{
        token_value = strdup(full_path);
	}
	if (!token_value)
    {
        perror("strdup");
        free(token);
        free(full_path);
        return (0);
    }
	token->token = token_value;
	token->type = ARG;
	token->is_quote = 0;

	return (0);
}

t_token	*create_token_from_entry(const char *dir_path, const char *entry_name)
{
	t_token	*new_token;
	char	*full_path;

	full_path = construct_full_path(dir_path, entry_name);
	if (!full_path)
		return (NULL);
	new_token = allocate_token();
	if (!new_token)
		return (free(full_path), NULL);
	if (initialize_token(new_token, full_path, dir_path, entry_name) < 0)
		return (free(full_path), NULL);
	return (free(full_path), new_token);
}

