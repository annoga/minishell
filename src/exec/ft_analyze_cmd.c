/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:11 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/03 19:51:02 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int		has_pipe(t_cmd *cmd);
static int		runs_in_pipes(t_cmd *command);
static t_cmd	*run_builtin(t_cmd *cmd, int *exit_status, t_env **env);
static int		op_condition_true(t_token_type operator, int status);

/* This function takes a series of commands and decides which to execute,
 * depending on the connections between them */
int	ft_analyze_cmd(t_env **env, t_cmd *current, int err_code)
{
	while (current)
	{
		if (current->cmd)
		{
			if (has_pipe(current) || runs_in_pipes(current))
				current = process_command_block(current, &err_code, *env, 0);
			else
			{
				if (current->connection_type == PIPE)
					current = skip_step(&err_code, env, current->next);
				else
					current = run_builtin(current, &err_code, env);
			}
		}
		else if (current->subcommand)
			err_code = ft_analyze_cmd(env, current->subcommand, 0);
		else
			current = process_command_block(current, &err_code, *env, 0);
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
static int	runs_in_pipes(t_cmd *command)
{
	char	*cmd_name;
	char	*cmd_arg;

	cmd_name = command->cmd[0];
	cmd_arg = command->cmd[1];
	if (!ft_strcmp(cmd_name, "exit"))
		if (command->connection_type != PIPE)
			return (0);
	if (!ft_strcmp(cmd_name, "unset"))
		return (0);
	if (!ft_strcmp(cmd_name, "export"))
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
	if (!ft_strcmp(cmd->cmd[0], "unset"))
		*exit_status = ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		*exit_status = ft_exit(cmd, 1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		*exit_status = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		*exit_status = ft_cd(cmd, *env);
	return (cmd);
}
