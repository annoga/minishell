/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/02 14:15:31 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		has_pipe(t_cmd *cmd);
static int		runs_in_pipes(t_cmd *command);
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env);
static int		op_condition_true(t_token_type operator, int status);

/* This function takes a series of commands and decides which to execute,
 * depending on the connections between them */
int	ft_analyze_cmd(t_env **env, t_cmd *current)
{
	int		err_code;

	err_code = 0;
	//printf("c1:%p\n", current->cmd);
	err_code = get_heredocs(current, env, 0);//if != 0, boom///internal 0-1
	//need to clear tmp_file if we don't have a cmd
	//printf("out of getheredocs\n");
	//printf("c2:%p\n", current->cmd);
	//printf("f:%p,fT:\n", current->files);
	//if (current->files && current->files->type == HEREDOC)
	//	printf("anFd:%d\n", current->files->heredoc_fd);
	if (err_code != 0)
		return (err_code);
	while (current)
	{
		if (current->cmd)
		{
			if (has_pipe(current) || runs_in_pipes(current))
				current = process_command_block(current, &err_code, *env);
			else
			{
				//if (current->files || current->connection_type == PIPE)
				if (current->connection_type == PIPE)
				{//ese ->files probablemente sobra. Testeamos antes de borrar
					err_code = ft_analyze_cmd(env, current->next);//lo saltamos
					current = NULL;
				}
				else
					current = run_builtin(current, &err_code, env);
			}
		}
		else if (current->subcommand)
			err_code = ft_analyze_cmd(env, current->subcommand);
		else//files, heredocs
			current = process_command_block(current, &err_code, *env);
		if (current && op_condition_true(current->connection_type, err_code))
			current = current->next;
		else
			return (err_code);
	}
	return (err_code);
}

static int	has_pipe(t_cmd *cmd)
{
	if (cmd->connection_type == PIPE)
		return (1);
	else
		return (0);
}

static int	op_condition_true(t_token_type operator, int status)
{
	if (operator == AND && status == 0)
		return (1);
	if (operator == OR && status != 0)
		return (1);
	return (0);
}

	//##COMMANDS##//
	//SUBCOMMANDS
	//1)if cmd->cmd == NULL, but subC != NULL, run subC as block
	//BUILTINS (PIPELESS)
	//1)if connection_type == PIPE, update to next cmd.
	//2)if connection_type == AND / OR, we run builtin as block.
	
	//##LINKS##//
	//AND 
	//1)run block. 
	//2)if err_code != 0, stop. else, update to next cmd and go to 1) 
	//OR
	//1)run block.
	//2)if err_code == 0, stop. else, update to next cmd and go to 1) 

/* This function filters those builtins that cannot run through a PIPE */
static int	runs_in_pipes(t_cmd *command)//igual tiene truco y la podemos ignorar.
{
	char	*cmd_name;
	char	*cmd_arg;

	cmd_name = command->cmd[0];
	cmd_arg = command->cmd[1];
	if (!ft_strcmp(cmd_name, "exit"))
		if (command->connection_type != PIPE)
			return (0);
	if (!ft_strcmp(cmd_name, "unset"))//Aunque entre, no tiene efecto
		return (0);
	if (!ft_strcmp(cmd_name, "export"))////OJO! export sin cmnd[1] sí puede PIPE!!!
		if (cmd_arg)
			return (0);
	if (!ft_strcmp(cmd_name, "cd"))
		return (0);
	return (1);
}

/* This function runs a builtin depending on input, then returns the 
 * appropriate exit status */
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env)
{
	//unset, export, cd. Any builtins that do NOT work with pipes
	if (!ft_strcmp(cmd->cmd[0], "unset"))
		*exit_status = ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))//sólo si NO tiene pipe
		*exit_status = ft_exit(cmd, 1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))//sólo si tiene args
		*exit_status = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))//sólo si NO tiene pipe
		*exit_status = ft_cd(cmd, *env);
	return (cmd);
}
