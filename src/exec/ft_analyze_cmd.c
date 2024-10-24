/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/24 17:45:13 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_env *env, t_cmd *cmnd)
{
	char	*path;
	char	**env_arr;
<<<<<<< HEAD
	// t_cmd	*cmnd;
//	int		i;//
//	i = 0;//
=======
	t_cmd	*cmnd;
	// int		i;//

	// i = 0;//
>>>>>>> cris
	env_arr = ft_get_env_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}
<<<<<<< HEAD
//	while (env_arr[i])//
//		printf("%s\n", env_arr[i++]);//print envp
	// cmnd = parser(head);//tb debe liberarse
=======
	// while (env_arr[i])//
	// 	printf("%s\n", env_arr[i++]);//print envp
	cmnd = parser(head);//tb debe liberarse
//	return (0);	
//	printf("cmd[0]:%s\n", cmnd->cmd[0]);
//	printf("cmd[1]:%s\n", cmnd->cmd[1]);
//	printf("cmd:%s\n", cmnd->heredoc[0]);//Uninitialised if empty
//	printf("next:%p\n", cmnd->next);//NULL if empty
//	printf("conType:%i\n", cmnd->connection_type);//NULL if empty

	//if cmd exists
>>>>>>> cris
	path = find_cmd_path(cmnd->cmd[0], ft_getenv("PATH", env));
	if (path == NULL)
		return (0);
	cmnd->path = path;
//	return (0);	
	printf("cmd[0]:%s\n", cmnd->cmd[0]);
	printf("cmd[1]:%s\n", cmnd->cmd[1]);
	printf("path:%s\n", cmnd->path);
	printf("next:%p\n", cmnd->next);//NULL if empty
	printf("conType:%i\n", cmnd->connection_type);//NULL if empty

	//if cmd exists
//	path[0] = '\n';
	int		err_code;
	pid_t	last_pid;
	pid_t	pid;
	t_pipe	fds;
	int	j;

	j = 0;

	while (cmnd)
	{
		if (cmnd->connection_type == PIPE)
		{
			pipe(fds.next);//msg if err?
		printf("dad - read:%i, write:%i\n",fds.next[READ],fds.next[WRITE]);
		}
	pid = do_fork();
	if (pid == 0)
	{
		exec_child(cmnd, fds, env_arr, j);
/*		if (cmnd->connection_type == PIPE)
		{
		printf("kid - read:%i, write:%i\n",fds.next[READ],fds.next[WRITE]);
	//command n0: dup input
	//command n0: dup input
/			if (j != 0)//movemos IN en el primero
				pipe_read_stdin(fds.next);
	//command ...(n - 1): dup output
			if (j == 0 || cmnd->next)//movemos OUT salvo en el último
				pipe_write_stdout(fds.next);
		}
	//command ...n: dup output to file, heredoc, or (1)
		if (cmnd->connection_type == REDIR_OUT)
			redir_file(cmnd->files->name, REDIR_OUT);
		if (cmnd->connection_type == APPEND)
			redir_file(cmnd->files->name, APPEND);

		execve(path, cmnd->cmd, env_arr);
		exit(1);//martillo de emergencia*/
	}
	last_pid = pid;
	//free path

	if (cmnd->connection_type == PIPE)
	{
		close(fds.next[WRITE]);
	}
	cmnd = cmnd->next;
	j++;
	}

	int	stat_loc;

	pid = wait(&stat_loc);
	if (pid == last_pid)
		err_code = stat_loc;
	if (WIFEXITED(err_code))
	{
<<<<<<< HEAD
		//printf("Im in WIFEXITED");
		err_code = WEXITSTATUS(err_code);
	}
//	printf("pid:%i\nlast_pid:%i\nerr_code:%i\n", pid, last_pid, err_code);
=======
		// printf("Im in WIFEXITED");
		err_code = WEXITSTATUS(err_code);
	}
	// printf("pid:%i\nlast_pid:%i\nerr_code:%i\n", pid, last_pid, err_code);
>>>>>>> cris


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
