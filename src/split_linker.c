#include "../inc/minishell.h"

t_token	*split_linker(char *line)
{
	t_token	*token;

	token = tokenizer(line);
	// token = check_bonus_token(token);


	print_list(token);
	// printf("\n");
	return (token);
}
