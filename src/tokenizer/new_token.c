#include "../../inc/minishell.h"

t_token *new_token(t_token_type type, char *value, int is_quote)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->token = value;
	token->is_quote = is_quote;
	token->next = NULL;
	return (token);
}
