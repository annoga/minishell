#include "../../inc/minishell.h"

static int	check_syntax_conditions(t_synt *state, t_token_type current_type)
{
	if ((state->expecting_cmd && (current_type == COMMAND || current_type == L_PAREN))
		|| (!state->has_content && ((current_type >= AND && current_type <= PIPE)
		|| current_type == R_PAREN))
		|| ((state->last_token_type >= REDIR_IN && state->last_token_type <= HEREDOC)
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

static int	check_syntax_error(t_token *token, t_synt *anal_data)
{
	if (token || ((anal_data->last_token_type < COMMAND || anal_data->last_token_type > FILES)
		&& anal_data->last_token_type != R_PAREN))
	{
		if (token)
			ft_printf("syntax error near unexpected token '%s'\n", token->token);
		else
			return_error("syntax error near unexpected token 'new line'");

		return (1);
	}
	return (0);
}

int analize_tokens(t_token *token)
{
    t_synt anal_data;

    ft_bzero(&anal_data, sizeof(t_synt));
    while (token)
    {
        token->syntaxis = assing_type(token->token, &anal_data);
        if (error_syntax(&anal_data, token->syntaxis))
            break;
        if (token->syntaxis == SPACE_TOKEN)
        {
            token = token->next;
            continue;
        }
        anal_data.last_token_type = token->syntaxis;
        token = token->next;
    }
    return (!check_syntax_error(token, &anal_data));
}


// SYNTAX
// (ls -l | grep txt) && (echo "Found" || echo "Not found")
// echo Hello | | grep World
// echo Hello && 
// Input: ((echo A && echo B) || (echo C && echo D)) | grep A

// Nested parentheses with logical operators and pipes.
// Expected Output: No syntax error.
// Input: (ls -l | grep txt) && cat < input.txt > output.txt

// Combining pipes, parentheses, and redirection.
// Expected Output: No syntax error.
// Input: echo Hello > file.txt && cat < file.txt || echo "Error"

// Combining redirection and logical operators.
// Expected Output: No syntax error.