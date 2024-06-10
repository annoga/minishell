#include "../../inc/minishell.h"

t_token *handle_special_dollar(char *line, int *i)
{
	int		start;
	char	*value;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\''
		&& line[*i] != '"' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|' && line[*i] != '(' && line[*i] != ')')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start - 1], (*i + 1)- start);
	if (!value)
		return (NULL);
	(*i)--;
	return (new_token(ARG, value, 0));
}



t_token	*handle_dollar(char *line, int *i)
{
	int		start;
	char	*value;

	start = ++*i;
	if(!ft_isalpha(line[start]) || line[start] == '_')
		return (handle_special_dollar(line, i));
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\''
		&& line[*i] != '"' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '|' && line[*i] != '(' && line[*i] != ')')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return (NULL);
	(*i)--;
	return (new_token(ENV, value, 0));
}
