/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 17:55:57 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 17:55:57 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	set_command(t_cmd **cmd, t_token *token)
{
	char	*tmp;

	if (!(*cmd))
		*cmd = add_command(cmd);
	if (!(*cmd))
		return (lstclear(cmd, del_command));
	tmp = ft_strdup(token->token);
	if (!tmp)
		return (lstclear(cmd, del_command));
	(*cmd)->cmd = add_dir((*cmd)->cmd, tmp);
	if (!(*cmd)->cmd)
		return (lstclear(cmd, del_command), free(tmp));
}

void	set_connection(t_token *token, t_cmd **command)
{
	t_cmd	*new_cmd;

	if (*command)
		(*command)->connection_type = token->syntaxis;
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (lstclear(command, del_command));
	(*command)->next = new_cmd;
	*command = new_cmd;
}

void	initialize_command_if_needed(t_cmd **command, t_cmd **head)
{
	if (!*command)
	{
		*command = add_command(command);
		*head = *command;
	}
}

static t_cmd	*parser_main(t_token *token, t_cmd *command, t_cmd *head)
{
	t_token	*last_tkn;

	last_tkn = NULL;
	while (token)
	{
		initialize_command_if_needed(&command, &head);
		if (is_argument_or_quote(token, &command, last_tkn)
			|| is_command_or_argument(token, &command)
			|| is_connection(token, &command))
			last_tkn = token;
		else if (is_redirection(&token, &command, &last_tkn)
			|| is_subcommand_start(&token, &command))
			continue ;
		else if (is_subcommand_end(token))
			return (head);
		last_tkn = token;
		token = token->next;
	}
	return (head);
}

t_cmd	*parser(t_token *token)
{
	t_cmd	*command;
	t_cmd	*head;

	command = NULL;
	head = NULL;
	return (parser_main(token, command, head));
}
