#include "../../inc/minishell.h"

char	*free_split(char **split)
{
	int	i;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}
