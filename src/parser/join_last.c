/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:22:00 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 01:22:02 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_argument_or_quote(t_token *token, t_cmd **command, t_token *last_tkn)
{
	if (last_tkn && token->type != SPACE_TOKEN
		&& (token->type == ARG || token->type == DOUBLE_QUOTE
			|| token->type == SINGLE_QUOTE || token->type == ENV)
		&& (last_tkn->syntaxis == COMMAND || last_tkn->syntaxis == ARG
			|| (last_tkn->syntaxis >= REDIR_IN
				&& last_tkn->syntaxis <= HEREDOC)))
	{
		ft_join_last(*command, token, last_tkn->syntaxis);
		return (1);
	}
	return (0);
}

static void	join_file(t_file *aux, t_token *token)
{
	char	*join;

	while (token && token->type != SPACE_TOKEN)
	{
		join = ft_strjoin(aux->name, token->token);
		free(aux->name);
		if (token->type == DOUBLE_QUOTE || token->type == SINGLE_QUOTE)
			aux->is_quoted = 1;
		aux->name = join;
		token->type = SPACE_TOKEN;
		token->syntaxis = SPACE_TOKEN;
		token = token->next;
	}
}

void	ft_join_last(t_cmd *cmd, t_token *token, t_token_type last_type)
{
	char	*join;
	t_file	*aux;
	int		i;

	i = 0;
	aux = cmd->files;
	if ((last_type == ARG || last_type == COMMAND) && cmd->cmd && cmd->cmd[0])
	{
		while (cmd->cmd[i + 1])
			i++;
		join = ft_strjoin(cmd->cmd[i], token->token);
		free(cmd->cmd[i]);
		cmd->cmd[i] = join;
	}
	else if ((last_type >= REDIR_IN && last_type <= HEREDOC)
		|| last_type == FILES || token->type == ENV)
	{
		while (aux && aux->next)
			aux = aux->next;
		join_file(aux, token);
	}
}
