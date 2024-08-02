#include "../../inc/minishell.h"

int ft_istoken(char c)
{
    if(!ft_isspace(c) && c == '\''
		&& c == '"' && c == '<' && c == '>'
		&& c == '|' && c == '(' && c == ')')
		return (1);
	return (0);
}