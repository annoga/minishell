#include "../../inc/minishell.h"

void	lst_add_back(void *lst, void *new)
{
	void	**aux;

	if (!lst || !new)
		return ;
	if (!*(void **)lst)
	{
		*(void **)lst = new;
		return ;
	}
	aux = *(void **)lst;
	while (*aux)
		aux = *aux;
	*aux = new;
}