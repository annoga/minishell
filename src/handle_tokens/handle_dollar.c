#include "../../inc/minishell.h"

t_token *handle_special_dollar(char *line, int *i)
{
	int		start;
	char	*value;
	int		new_env;

	start = ++*i;
	new_env = 0;
	while (line[*i] && !ft_istoken(line[*i]) && !ft_isalpha(line[*i]))
	{
		(*i)++;
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		
		while(line[*i] && line[*i] == '$')
		{
			(*i)++;
			if((ft_isalpha(line[*i]) || line[*i] == '_'))
			{
				new_env = 1;
				break ;
			}
		}
	}
	// value = ft_strndup(&line[start - 1], (*i + 1)- start);
	value = ft_strndup(&line[start], (*i)- start);
	printf("new_env: %d\n", new_env);
	printf("value: %s\n", value);
	if (!value)
		return (NULL);
	if (new_env)
		(*i) -= 2;
	else
		(*i) -= 1;
	return (new_token(ARG, value, 0));
}



t_token	*handle_dollar(char *line, int *i)
{
	int		start;
	char	*value;

	start = *i;
	printf("holi\n");
	if(!ft_isalpha(line[start + 1]) && line[start + 1] != '_')
		return (handle_special_dollar(line, i));
	printf("handle %s\n", &line[start]);

	start = ++*i;
	while (line[*i] && (ft_isalpha(line[*i]) || line[*i] == '_'))
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	printf("start: %d\n", start);
	printf("i: %d\n", *i);
	value = ft_strndup(&line[start], *i - start);
	printf("value: %s\n", value);
	if (!value)
		return (NULL);
	(*i)--;
	return (new_token(ENV, value, 0));
}
