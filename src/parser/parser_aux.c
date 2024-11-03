/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_aux.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/03 17:47:22 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/11/03 17:48:35 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	is_command_or_argument(t_token *token, t_cmd **command)
{
	if (token->syntaxis == COMMAND || token->syntaxis == ARG)
	{
		set_command(command, token);
		return (1);
	}
	return (0);
}

int	is_connection(t_token *token, t_cmd **command)
{
	if (token->syntaxis == AND || token->syntaxis == OR
		|| token->syntaxis == PIPE)
	{
		set_connection(token, command);
		return (1);
	}
	return (0);
}

int	is_redirection(t_token **token, t_cmd **command, t_token **last_tkn)
{
	if ((*token)->syntaxis >= REDIR_IN && (*token)->syntaxis <= HEREDOC)
	{
		*last_tkn = *token;
		set_file(command, token);
		return (1);
	}
	return (0);
}

int	is_subcommand_start(t_token **token, t_cmd **command)
{
	if ((*token)->syntaxis == L_PAREN)
	{
		set_subcommand(command, token);
		return (1);
	}
	return (0);
}

int	is_subcommand_end(t_token *token)
{
	if (token->syntaxis == R_PAREN)
		return (1);
	return (0);
}
