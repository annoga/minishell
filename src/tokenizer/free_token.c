#include "../../inc/minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->type == ARG || tmp->type == SINGLE_QUOTE 
			|| tmp->type == DOUBLE_QUOTE || tmp->type == L_PAREN 
			|| tmp->type == R_PAREN)
		{
			free(tmp->token);
			tmp->token = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
}
