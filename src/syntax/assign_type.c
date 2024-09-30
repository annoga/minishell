#include "../../inc/minishell.h"

static t_token_type	ft_gettokentype(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "&&", 2))
		return (AND);
	if (!ft_strncmp(str, "||", 2))
		return (OR);
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	if (!ft_strncmp(str, " ", 1))
		return (SPACE_TOKEN);
	if (!ft_strncmp(str, "(", 1))
		return (L_PAREN);
	if (!ft_strncmp(str, ")", 1))
		return (R_PAREN);
	if (!ft_strncmp(str, "<", 1))
		return (REDIR_IN);
	if (!ft_strncmp(str, ">", 1))
		return (REDIR_OUT);
	return (0);
}

static t_token_type	check_current_type(char *token, t_synt *state)
{
	t_token_type	current_type;

	current_type = ft_gettokentype(token);
	if (current_type == SPACE_TOKEN)
		return (SPACE_TOKEN);

	if (current_type && current_type >= AND && current_type <= R_PAREN)
		state->is_cmd_assigned = 0;

	return (current_type);
}

t_token_type	assing_type(char *token, t_synt *state)
{
	t_token_type	current_type;

	if (!token)
		return (NO_TYPE);

	current_type = check_current_type(token, state);
	if (current_type)
		return (current_type);

	if (state->last_token_type >= REDIR_IN && state->last_token_type <= HEREDOC)
		return (FILES);

	if (state->is_cmd_assigned)
		return (ARG);

	state->is_cmd_assigned = 1;
	return (COMMAND);
}