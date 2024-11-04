/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:15:28 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 23:00:50 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token_type	ft_gettokentype(char *str, t_token_type type)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "&&") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (AND);
	if (!ft_strcmp(str, "||") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (OR);
	if (!ft_strcmp(str, "<<") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (HEREDOC);
	if (!ft_strcmp(str, ">>") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (APPEND);
	if (!ft_strcmp(str, "|") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (PIPE);
	if (!ft_strcmp(str, " ") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (SPACE_TOKEN);
	if (!ft_strcmp(str, "(") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (L_PAREN);
	if (!ft_strcmp(str, ")") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (R_PAREN);
	if (!ft_strcmp(str, "<") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (REDIR_IN);
	if (!ft_strcmp(str, ">") && type != DOUBLE_QUOTE && type != SINGLE_QUOTE)
		return (REDIR_OUT);
	if (type == DOUBLE_QUOTE || type == SINGLE_QUOTE)
		return (ARG);
	return (0);
}

static t_token_type	check_current_type(char *token, t_synt *state,
			t_token_type type)
{
	t_token_type	current_type;

	current_type = ft_gettokentype(token, type);
	if (current_type == SPACE_TOKEN)
		return (SPACE_TOKEN);
	if (current_type && current_type >= AND && current_type <= R_PAREN)
		state->is_cmd_assigned = 0;
	return (current_type);
}

t_token_type	assign_type(char *token, t_synt *state, t_token_type type)
{
	t_token_type	current_type;

	if (!token)
		return (NO_TYPE);
	current_type = check_current_type(token, state, type);
	if (current_type)
		return (current_type);
	if (state->last_token_type >= REDIR_IN && state->last_token_type <= HEREDOC)
		return (FILES);
	if (state->is_cmd_assigned)
		return (ARG);
	state->is_cmd_assigned = 1;
	return (COMMAND);
}
