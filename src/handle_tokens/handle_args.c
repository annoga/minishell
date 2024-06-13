#include "../../inc/minishell.h"

t_token	*handle_arg(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\''
		&& line[*i] != '"' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|' && line[*i] != '(' && line[*i] != ')'
		&& line[*i] != '$')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	token = new_token(ARG, value, 0);
	(*i)--;
	return (token);
}
