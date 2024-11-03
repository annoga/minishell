/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 tokenizer.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <crmanzan@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/30 21:49:33 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 16:24:31 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_token	*tokenizer(char *line, t_env *env)
{
	t_token	*head_token;
	t_token	*token;
	int		i;
	int		is_hdoc;

	is_hdoc = 0;
	head_token = NULL;
	i = 0;
	while (line[i])
	{
		token = get_token(line, &i, env, is_hdoc);
		if (!token)
			return (NULL);
		if (is_hdoc && token->type != SPACE_TOKEN)
			is_hdoc = 0;
		if (token->type == HEREDOC)
			is_hdoc = 1;
		add_token(&head_token, token);
		i++;
	}
	return (head_token);
}
