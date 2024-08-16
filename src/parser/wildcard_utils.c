/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 wildcard_utils.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/08/13 20:42:36 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/08/13 20:42:39 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

DIR	*open_directory(const char *dir_path)
{
	DIR	*dir;
	
	dir = opendir(dir_path);
	if (!dir)
		perror("bash: ");
	return (dir);
}

static void	insert_token_sorted(t_token **new_tokens, t_token *new_token)
{
    t_token	*current;
    t_token	*previous;

    if (!(*new_tokens) || ft_strncmp(new_token->token, (*new_tokens)->token) < 0)
    {
        new_token->next = *new_tokens;
        *new_tokens = new_token;
    }
    else
    {
        previous = NULL;
        current = *new_tokens;
        while (current && ft_strncmp(new_token->token, current->token) >= 0)
        {
            previous = current;
            current = current->next;
        }
        new_token->next = current;
        previous->next = new_token;
    }
}

static void	add_matching_token(const char *entry_name, const char *pattern,
				t_token **new_tokens, t_token **last_token)
{
	t_token	*new_token;

	(void)last_token;
	if (ft_fnmatch(pattern, entry_name) == 0) 
	{
		new_token = create_token_from_entry(".", entry_name);
		if (new_token) 
		{
			insert_token_sorted(new_tokens, new_token);
		}
	}
}

static int	is_valid_entry(const char *entry_name)
{
	if (ft_strncmp(entry_name, ".") != 0 && ft_strncmp(entry_name, "..") != 0)
		return 1;
	return 0;
}

void	process_directory_entries(DIR *dir, const char *pattern,
				t_token **new_tokens, t_token **last_token)
{
	struct dirent	*entry;

	while ((entry = readdir(dir)) != NULL)
	{
		if (is_valid_entry(entry->d_name))
			add_matching_token(entry->d_name, pattern, new_tokens, last_token);
	}
	
	sort_alphabetic_token(*new_tokens);
}
