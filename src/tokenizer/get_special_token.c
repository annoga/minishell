#include "../../inc/minishell.h"

t_token	*get_special_token(char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
		return (create_token(OR, "||", i));
	else if (line[*i] == '|')
		return (create_token(PIPE, "|", i));
	else if (line[*i] == '&' && line[*i + 1] == '&')
		return (create_token(AND, "&&", i));
	else if (line[*i] == '\'')
		return (handle_single_quote(line, i));
	else if (line[*i] == '"')
		return (handle_double_quote(line, i));
	else if (line[*i] == '$')
		return (handle_dollar(line, i));
	return (NULL);
}
