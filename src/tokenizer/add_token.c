#include "../../inc/minishell.h"

void add_token(t_token **head, t_token *new)
{
	t_token *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new;
}