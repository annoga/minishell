/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:32:41 by angeln            #+#    #+#             */
/*   Updated: 2024/10/30 09:53:33 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//static void		fill_cmd_paths(t_cmd *cmd, char *envpaths);

// int check_dollar(char *line)
// {
// 	int *i;
// 	*i = 0;
// 	while (line[*i])
// 	{
// 		if (line[*i] == '$')
// 			return (1);
// 		(*i)++;
// 	}
// 	return (0);
// }

// t_token *check_env(t_token *token)
// {
// 	t_token *tmp;


// 	while(token)
// 	{
// 		tmp = token;
// 		if (tmp->type == ARG)
// 		{
// 			if(check_dollar(tmp->token))
// 			{
// 				printf(" $$$$$ token: %s\n", tmp->token);
// 				tmp->type = ENV;
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (tmp);
// }


t_token	*split_linker(char *line, t_env **env)
{
	t_token	*token;
	t_cmd	*cmd;

	token = tokenizer(line);
	// token = check_env(token);
	token = expansor(token, env);

	if(!analize_tokens(token))
		return(free_token(&token), NULL);
	// prueba builtin
	cmd = parser(token);
	//fill_cmd_paths(cmd, ft_getenv("PATH", *env));//lo moveré a process_child
	
	if (debug == 1)//FOR TESTING ONLY, DELETE
		print_list(token);
	// printf("\n");
	token = command_analyzer(token, env, cmd);
	free_token(&token);
	token = NULL;
	free_tcmd(&cmd);
	cmd = NULL;
	return (token);
}

/* Sets a possible path for each command, or NULL if none is found */
/*static void	fill_cmd_paths(t_cmd *cmd, char *envpaths)
{
	t_cmd	*tmp_cmd;
	char	*path;

	tmp_cmd = cmd;
	path = NULL;
	while (tmp_cmd)
	{
		if (tmp_cmd->cmd)
			path = get_cmd_path(tmp_cmd->cmd[0], envpaths);
		tmp_cmd->path = path;
		path = NULL;
		if (tmp_cmd->subcommand)
			fill_cmd_paths(tmp_cmd->subcommand, envpaths);
		tmp_cmd = tmp_cmd->next;
	}
}*/
