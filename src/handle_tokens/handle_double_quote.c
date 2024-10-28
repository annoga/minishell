/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 handle_double_quote.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/28 17:37:22 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/10/28 17:41:02 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/minishell.h"

char	*append_str(char *result, char *str)
{
	char	*new_result;

	if (!result)
		return (str);
	new_result = (char *)malloc(strlen(result) + strlen(str) + 1);
	if (!new_result)
		return (NULL);
	ft_strncpy(new_result, result, ft_strlen(result) + 1);
	ft_strlcat(new_result, str, ft_strlen(result) + ft_strlen(str) + 1);
	free(result);
	free(str);
	return (new_result);
}

char	*handle_env_var(char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*env_value;

	start = *i;
	while (line[*i] && (ft_isalpha(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(&line[start], *i - start);
	if (!var_name)
		return (NULL);
	env_value = getenv(var_name);
	free(var_name);
	if (env_value)
		return (ft_strdup(env_value));
	return (ft_strdup(""));
}

char	*parse_and_append_env_var(char *result, char *line, int *i, int *start)
{
	char	*temp;

	if (*start < *i)
	{
		temp = ft_strndup(&line[*start], *i - *start);
		result = append_str(result, temp);
	}
	(*i)++;
	temp = handle_env_var(line, i);
	result = append_str(result, temp);
	*start = *i;
	return (result);
}

char	*parse_double_quote_content(char *line, int *i)
{
	int		start;
	char	*result;
	char	*temp;

	start = *i;
	*result = NULL;
	result = append_str(result, ft_strdup("\""));
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$' && (ft_isalpha(line[*i + 1])
				|| line[*i + 1] == '_'))
			result = parse_and_append_env_var(result, line, i, &start);
		else
			(*i)++;
	}
	if (start < (*i))
	{
		temp = ft_strndup(&line[start], *i - start);
		result = append_str(result, temp);
	}
	result = append_str(result, ft_strdup("\""));
	return (result);
}

t_token	*handle_double_quote(char *line, int *i)
{
	char	*result;
	t_token	*token;

	(*i)++;
	result = parse_double_quote_content(line, i);
	if (line[*i] == '"')
		(*i)++;
	if (!result)
		result = ft_strdup("");
	token = new_token(DOUBLE_QUOTE, result);
	(*i)--;
	return (token);
}
// t_token	*handle_double_quote(char *line, int *i)
// {
//	int		start;
//	char	*value;
//	t_token	*token;

//	start = ++(*i);
//	while (line[*i] && line[*i] != '"')
//	{
//		(*i)++;
//	}
//	printf("sdahj\n");
//	value = ft_strndup(&line[start], *i - start);
//	if (!value)
//		return (NULL);
//	token = new_token(DOUBLE_QUOTE, value, 1);
//	return (token);
// }
