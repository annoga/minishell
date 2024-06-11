
#include "../../inc/minishell.h"

t_token	*handle_double_quote(char *line, int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strndup(&line[*i], 1);
	if (!value)
		return (NULL);
	token = new_token(DOUBLE_QUOTE, value, 0);
	return (token);
}

// t_token	*handle_double_quote(char *line, int *i)
// {
// 	int		start;
// 	char	*value;
// 	t_token	*token;
// 	int 	is_env;

// 	start = ++(*i);
// 	is_env = 0;
// 	while (line[*i] && line[*i] != '"')
// 	{
// 		if (line[*i] == '$')
// 			is_env = 1;	
// 		(*i)++;
// 	}
// 	if(line[start] == '$')
// 	{
// 		is_env = 1;
// 		start++;
// 	}
// 	if (line[*i] != '"')
// 		return(return_error("Error: missing quote\n"));
// 	printf("sdahj\n");
// 	value = ft_strndup(&line[start], *i - start);
// 	if (!value)
// 		return (NULL);
// 	if(is_env)
// 		token = new_token(ENV, value, 1);
// 	else
// 		token = new_token(DOUBLE_QUOTE, value, 1);
// 	return (token);
// }

