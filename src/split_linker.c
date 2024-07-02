#include "../inc/minishell.h"
// int check_dollar(char *line)
// {
// 	int *i;
// 	*i = 0;
// 	while (line[*i])
// 	{
// 		if (line[*i] == '$')
// 			return (1);
// 		(*i)++;
// 	}
// 	return (0);
// }

// t_token *check_env(t_token *token)
// {
// 	t_token *tmp;


// 	while(token)
// 	{
// 		tmp = token;
// 		if (tmp->type == ARG)
// 		{
// 			if(check_dollar(tmp->token))
// 			{
// 				printf(" $$$$$ token: %s\n", tmp->token);
// 				tmp->type = ENV;
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (tmp);
// }


t_token	*split_linker(char *line)
{
	t_token	*token;

	token = tokenizer(line);
	// token = check_env(token);
//	token = prueba_env(token);
	// prueba builtin
	token = mock_builtin_tokenizer(token);


	print_list(token);
	// printf("\n");
	return (token);
}
