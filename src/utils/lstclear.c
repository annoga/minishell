#include "../../inc/minishell.h"

void	lstclear(void *list, void (*del)(void *))
{
	void	**aux;
	void	*tmp;

	if (!list || !del)
		return ;
	aux = *(void **)list;
	while (aux)
	{
		tmp = *aux;
		del(aux);
		free(aux);
		aux = tmp;
	}
	*(void **)list = NULL;
}