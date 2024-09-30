#include "../../inc/minishell.h"

static t_token	*find_subcommand_tokens(t_token *token, int *parenthesis_count)
{
	while (token && *parenthesis_count > 0)
	{
		if (token->syntaxis == L_PAREN)
			(*parenthesis_count)++;
		else if (token->syntaxis == R_PAREN)
			(*parenthesis_count)--;
		token = token->next;
	}
	return (token);
}

void	set_subcommand(t_cmd **cmd, t_token **tkn_p)
{
    t_cmd	*sub_cmd;
    t_token	*start_token;
    int		parenthesis_count;

    if (!(*cmd))  // Create a new command node if it doesn't exist
        *cmd = add_command(cmd);
    if (!(*cmd))
        return (lstclear(cmd, del_command));  // Memory cleanup in case of failure

    // Keep track of the start token and parenthesis level
    start_token = (*tkn_p)->next;
    parenthesis_count = 1;
	*tkn_p = find_subcommand_tokens(start_token, &parenthesis_count);

    // Parse the tokens within the parentheses and get the head of the subcommand list
    sub_cmd = parser(start_token);  // Parse from the token after '(' to the token before ')'
    if (!sub_cmd)
        return (lstclear(cmd, del_command));  // Cleanup if parsing fails

    // Assign the parsed subcommand list to the current command's subcommand field
    (*cmd)->subcommand = sub_cmd;
    (*cmd)->parenthesis = 1;

}