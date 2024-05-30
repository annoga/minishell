#include "../inc/minishell.h"

t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->token = value;
    token->next = NULL;
    return (token);
}

t_token *create_token(char type, char *value, int *i)
{
    t_token *token;

    printf("value: %s\n", value);
    if(!ft_strncmp(value, ">>") || !ft_strncmp(value, "<<") ||  !ft_strncmp(value, "&&") || !ft_strncmp(value, "||"))
        (*i)++;
    token = new_token(type, value);
    return (token);
}
t_token *handle_single_quote(char *line, int *i)
{
    int start;
    char *value;
    t_token *token;

	start = ++(*i);
    while(line[*i] && line[*i] != '\'')
        (*i)++;
    if(line[*i] != '\'')
    {
        printf("Error: missing quote\n");
        return (NULL);
    }
    value = ft_strndup(&line[start], *i - start);
    if(!value)
        return (NULL);
    token = new_token(SINGLE_QUOTE, value);
    return (token);
}

t_token	*handle_double_quote(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = ++(*i);
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] != '"')
	{
		printf("Error: missing quote\n");
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		return(NULL);
	token = new_token(DOUBLE_QUOTE, value);

	return (token);
}

t_token *handle_arg(char *line, int *i)
{
    int start;
    char *value;
    t_token *token;

    start = *i;
    while(line[*i] && !ft_isspace(line[*i]) && line[*i] != '\'' && line[*i] != '"' && line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
    {
        if(line[*i] == '&' && line[*i + 1] == '&')
            break;
        (*i)++;
    }
    value = ft_strndup(&line[start], *i - start);
    if(!value)
        return (NULL);
    token = new_token(ARG, value);
    (*i)--;
    return (token);
}
t_token *handle_space(char *line, int *i)
{
    while(line[*i] && ft_isspace(line[*i]))
        (*i)++;
    (*i)--;
    return create_token(SPACE, " ", i);
}

t_token *handle_special_token(char *line, int *i)
{
    // if (line[*i] == '(')
    //     return create_basic_token(LPAREN, "(", i);
    // else if (line[*i] == ')')
    //     return create_basic_token(RPAREN, ")", i);
    if (line[*i] == '|' && line[*i + 1] == '|')
        return create_token(OR, "||", i);
    else if (line[*i] == '|')
        return create_token(PIPE, "|", i);
    else if (line[*i] == '&' && line[*i + 1] == '&')
        return create_token(AND, "&&", i);
    return NULL;
}

t_token *get_token(char *line, int *i)
{
    t_token *token;
    token = handle_special_token(line, i);
    if(token)
        return (token);
    else if(line[*i] == '<' && line[*i + 1] == '<')
        token = create_token(HEREDOC, "<<", i);
    else if(line[*i] == '>' && line[*i + 1] == '>')
        token = create_token(APPEND, ">>", i);
    else if(line[*i] == '<')
        token = create_token(REDIR_IN, "<", i);
    else if(line[*i] == '>')
        token = create_token(REDIR_OUT, ">", i);
    else if(line[*i] == '\'')
        token = handle_single_quote(line, i);
    else if(line[*i] == '"')
        token = handle_double_quote(line, i);
    else if(ft_isspace(line[*i]))
    {
        token = handle_space(line, i);
    }
    else
        token = handle_arg(line, i);
    return (token);
}


t_token *new_split(char *line)
{
    t_token *head_token;
    t_token *token;
    int i;

    head_token = NULL;
    i = 0;
    while (line[i])
    {
        token = get_token(line, &i);
        if(!token)
            return (NULL);
        add_token(&head_token, token);
        i++;
    }
    return (head_token);
}