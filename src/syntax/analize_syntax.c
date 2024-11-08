/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angeln <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:15:14 by angeln            #+#    #+#             */
/*   Updated: 2024/11/04 22:59:21 by angeln           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_syntax_conditions(t_synt *state, t_token_type current_type)
{
	if ((state->expecting_cmd && (current_type == COMMAND
				|| current_type == L_PAREN)) || (!state->has_content
			&& ((current_type >= AND && current_type <= PIPE)
				|| current_type == R_PAREN))
		|| ((state->last_token_type >= REDIR_IN
				&& state->last_token_type <= HEREDOC)
			&& current_type != FILES))
		return (1);
	return (0);
}

static void	update_state_flags(t_synt *state, t_token_type current_type)
{
	if (current_type == COMMAND || current_type == R_PAREN)
		state->expecting_cmd = 1;
	else if (current_type >= AND && current_type <= PIPE)
	{
		state->expecting_cmd = 0;
		state->has_content = 0;
	}
	if (current_type >= REDIR_IN && current_type <= COMMAND)
		state->has_content = 1;
	if (current_type == L_PAREN)
		state->parenthesis_balance += 1;
	else if (current_type == R_PAREN)
		state->parenthesis_balance -= 1;
}

static int	error_syntax(t_synt *state, t_token_type current_type)
{
	if (current_type == SPACE_TOKEN)
		return (0);
	if (check_syntax_conditions(state, current_type))
		return (1);
	update_state_flags(state, current_type);
	return (state->parenthesis_balance < 0);
}

static int	check_syntax_error(t_token *token, t_synt *anal_data, t_env *env)
{
	if (token || ((anal_data->last_token_type < COMMAND
				|| anal_data->last_token_type > FILES)
			&& anal_data->last_token_type != R_PAREN))
	{
		if (token)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '",
				2);
			ft_putstr_fd(token->token, 2);
			ft_putendl_fd("'", 2);
		}
		env->exit_status = 2;
		return (1);
	}
	return (0);
}

int	analize_tokens(t_token *token, t_env *env)
{
	t_synt	anal_data;

	ft_bzero(&anal_data, sizeof(t_synt));
	while (token)
	{
		token->syntaxis = assign_type(token->token, &anal_data, token->type);
		if (error_syntax(&anal_data, token->syntaxis))
			break ;
		if (token->syntaxis == SPACE_TOKEN)
		{
			token = token->next;
			continue ;
		}
		anal_data.last_token_type = token->syntaxis;
		token = token->next;
	}
	return (!check_syntax_error(token, &anal_data, env));
}
