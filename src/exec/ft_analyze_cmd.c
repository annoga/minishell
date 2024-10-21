/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/21 13:49:28 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_token *head, t_env *env)
{
	char	*path;
	char	**env_arr;
	t_cmd	*cmnd;
//	int		i;

//	i = 0;
	env_arr = ft_get_env_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}
//	while (envp[i])
//		printf("%s\n", envp[i++]);//print envp
	cmnd = parser(head);//tb debe liberarse
//	printf("cmd[0]:%s\n", cmnd->cmd[0]);
//	printf("cmd[1]:%s\n", cmnd->cmd[1]);
//	printf("cmd:%s\n", cmnd->heredoc[0]);//Uninitialised if empty
//	printf("next:%p\n", cmnd->next);//NULL if empty
//	printf("conType:%i\n", cmnd->connection_type);//NULL if empty

	//if cmd exists
	path = find_cmd_path(cmnd->cmd[0], ft_getenv("PATH", env));
//	path[0] = '\n';
//	printf("path:%s\n", path);
	execve(path, cmnd->cmd, env_arr);

	//while (cmd)//lista de t_cmd
	//REDIR
//	if (head->type == REDIR_IN || head->type == REDIR_OUT)
	//	ft_redir(token, fd) --> 0, 1
	//CMD
	//if (.... COMMAND)
	//	ft_check_cmd
	//	ft_do_cmd
	//PIPE
	//if (PIPE)
	//	ft_redir(token, fd) --> 0
	//...and start again
//	ft_validate_cmd

	//have args? 
/*	if (!ft_strchr(path, '/'))
		path = find_cmd(path, env);
	is_valid_path(path);
	//printerror(path);
	//exit(1);//fail
	printf("Here: %s\n", head->token);*/
	return (0);
}
