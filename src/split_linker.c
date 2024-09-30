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


t_token	*split_linker(char *line, t_env **env)
{
	t_token	*token;

	token = tokenizer(line);
	// token = check_env(token);

	if(!analize_tokens(token))
		return(NULL);
	token = expansor(token);
	// prueba builtin

	if (debug == 1)//FOR TESTING ONLY, DELETE
		print_list(token);
	// printf("\n");
	token = mock_builtin_tokenizer(token, env);
	return (token);
}
