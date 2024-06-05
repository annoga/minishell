
#include "../../inc/minishell.h"

t_token	*handle_double_quote(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = ++(*i);
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] != '"')
	{
		printf("Error: missing quote\n");
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(DOUBLE_QUOTE, value);
	return (token);
}
