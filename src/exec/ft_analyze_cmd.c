/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/10/23 16:33:04 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Opens the given filename, redirects output to it, then closes it*/
int	redir_file(char *filename, int mode)
{
	int	fd;

	if (mode == REDDIR_OUT)
	{
		fd = open(cmnd->files->name, O_WRONLY | O_CREAT | O_TRUNC,
				OPEN_FILE_MODE)
	}
	else if (mode == APPEND)
	{
		fd = open(cmnd->files->name, O_WRONLY | O_CREAT | O_APPEND,
				OPEN_FILE_MODE)
	}
	dup2(fd, 1);//err msg?
	close(fd);
	return (0);//return exit code
}

/* Links standard input to our pipe's output */
void	dup_in_to_pipe(int *pipe)
{
	close(pipe[WRITE]);
	dup2(pipe[READ], 0);
	close(pipe[READ]);
}

/* Links standard output to our pipe's input */
void	dup_out_to_pipe(int *pipe)
{
	close(pipe[READ]);
	dup2(pipe[WRITE], 1);
	close(pipe[WRITE]);
}

/* This function takes one or more commands and goes through them */
int	ft_analyze_cmd(t_token *head, t_env *env)
{
	char	*path;
	char	**env_arr;
	t_cmd	*cmnd;
	int		i;//

	i = 0;//
	env_arr = ft_get_env_array(env);//need to free_split when done
	if (!env_arr)
	{
		printf("error translating t_env\n");
		return (0);
	}
	while (env_arr[i])//
		printf("%s\n", env_arr[i++]);//print envp
	cmnd = parser(head);//tb debe liberarse
//	return (0);	
//	printf("cmd[0]:%s\n", cmnd->cmd[0]);
//	printf("cmd[1]:%s\n", cmnd->cmd[1]);
//	printf("cmd:%s\n", cmnd->heredoc[0]);//Uninitialised if empty
//	printf("next:%p\n", cmnd->next);//NULL if empty
//	printf("conType:%i\n", cmnd->connection_type);//NULL if empty

	//if cmd exists
	path = find_cmd_path(cmnd->cmd[0], ft_getenv("PATH", env));
	if (path == NULL)
		return (0);
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
			pipe(fds->next);//msg if err?
	pid = do_fork();
	if (pid == 0)
	{
		if (cmnd->connection_type == PIPE)
		{
	//command n0: dup input
			if (j != 0)//movemos IN en el primero
				dup_in_to_pipe(fds->next);
	//command ...(n - 1): dup output
			if (j == 0 || cmnd->next)//movemos OUT salvo en el último
				dup_out_to_pipe(fds->next);
		}
	//command ...n: dup output to file, heredoc, or (1)
		if (cmnd->connection_type == REDIR_OUT)
			redir_file(cmnd->files->name, REDDIR_OUT);
		if (cmnd->connection_type == APPEND)
			redir_file(cmnd->files->name, APPEND);

		execve(path, cmnd->cmd, env_arr);
		exit(1);//martillo de emergencia
	}
	last_pid = pid;
	//free path
	cmnd = cmnd->next;
	j++;
	}

	int	stat_loc;

	pid = wait(&stat_loc);
	if (pid == last_pid)
		err_code = stat_loc;
	if (WIFEXITED(err_code))
	{
		printf("Im in WIFEXITED");
		err_code = WEXITSTATUS(err_code);
	}
	printf("pid:%i\nlast_pid:%i\nerr_code:%i\n", pid, last_pid, err_code);


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
