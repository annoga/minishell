#include "../../inc/minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->token);
		tmp->token = NULL;
		free(tmp);
		tmp = NULL;
	}
}
