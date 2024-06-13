#include "../../inc/minishell.h"

t_token	*handle_single_quote(char *line, int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strndup(&line[*i], 1);
	if (!value)
		return (NULL);
	token = new_token(SINGLE_QUOTE, value, 0);
	return (token);
}


// t_token	*handle_single_quote(char *line, int *i)
// {
// 	int		start;
// 	char	*value;
// 	t_token	*token;

// 	start = ++(*i);
// 	while (line[*i] && line[*i] != '\'')
// 		(*i)++;
// 	if (line[*i] != '\'')
// 	{
// 		printf("Error: missing quote\n");
// 		return (NULL);
// 	}
// 	value = ft_strndup(&line[start], *i - start);
// 	if (!value)
// 		return (NULL);
// 	token = new_token(SINGLE_QUOTE, value, 0);
// 	return (token);
// }
