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
		if(line[*i] == '$')
			break ;
	}
	printf("dollar line: %s\n", line);
	printf("line[i]: %c\n", line[*i]);
	value = ft_strndup(&line[start - 1], (*i + 1)- start);
	// value = ft_strndup(&line[start - 1], (*i + 1)- start);
	printf("value: %s\n", value);
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
	printf("line[start]: %c\n", line[start]);
	if(!ft_isalpha(line[start]) && line[start] != '_')
		return (handle_special_dollar(line, i));
	while (line[*i] && (ft_isalpha(line[*i]) || line[*i] == '_'))
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
