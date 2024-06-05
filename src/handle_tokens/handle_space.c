
#include "../../inc/minishell.h"

t_token	*handle_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	(*i)--;
	return (create_token(SPACE_TOKEN, " ", i));
}
