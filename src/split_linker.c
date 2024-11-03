/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:32:41 by angeln            #+#    #+#             */
/*   Updated: 2024/11/03 16:25:28 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*split_linker(char *line, t_env **env)
{
	t_token	*token;
	t_cmd	*cmd;

	token = tokenizer(line, *env);
	token = expansor(token, env, 0, 0);
	if(!analize_tokens(token, *env))
		return(free_token(&token), NULL);
	cmd = parser(token);
	free_token(&token);
	token = NULL;
	command_analyzer(env, cmd);
	free_tcmd(&cmd);
	cmd = NULL;
	return (token);
}
