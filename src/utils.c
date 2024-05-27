#include "../inc/minishell.h"
int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;
    size_t  n1;
    size_t  n2;
    size_t  n;

    n1 = ft_strlen(s1);
    n2 = ft_strlen(s2);
	i = 0;
    if(n1 > n2)
        n = n1;
    else
    {
        n = n2;
    }
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

t_token	*ft_lstnew(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = content;
    check_token(new);
    printf("token: %s, is_builtin: %d, is_pipe: %d, is_redir: %d, is_arg: %d, is_bonus: %d\n", new->token, new->is_builtin, new->is_pipe, new->is_redir, new->is_arg, new->is_bonus);
	new->next = NULL;
	return (new);
}

void check_token(t_token *head)
{
    check_builtin(head);
    check_pipe_bonus(head);
    check_redirect(head);
    if(!head->is_builtin && !head->is_pipe && !head->is_redir && !head->is_bonus)
    {
        printf("IS ARG ------->>> %s\n", head->token);
        head->is_arg = 1;
    }
    else
        head->is_arg = 0;
}
void check_pipe_bonus(t_token *head)
{
    t_token *tmp;

    tmp = head;
    if(!ft_strncmp(tmp->token, "|"))
    {
        printf("IS PIPE ------->>> %s\n", tmp->token);
        head->is_pipe = 1;
        head->is_bonus = 0;
    }
    else if(!ft_strncmp(tmp->token, "||") || !ft_strncmp(tmp->token, "&&"))
    {
        printf("IS BONUS ------->>> %s\n", tmp->token);
        head->is_pipe = 0;
        head->is_bonus = 1;
    }
    else
    {    
        head->is_pipe = 0;
        head->is_bonus = 0;
    }
}

void check_redirect(t_token *head)
{
    t_token *tmp;

    tmp = head;
    if(!ft_strncmp(tmp->token, ">") || !ft_strncmp(tmp->token, ">>") ||
        !ft_strncmp(tmp->token, "<") || !ft_strncmp(tmp->token, "<<"))
    {
        head->is_redir = 1;
        printf("IS REDIRECT ------->>> %s\n", tmp->token);
    }
    else
        head->is_redir = 0;
}

void check_builtin(t_token *head)
{
    t_token *tmp;

    tmp = head;
    if(!ft_strncmp(tmp->token, "echo") || !ft_strncmp(tmp->token, "cd") ||
        !ft_strncmp(tmp->token, "pwd") || !ft_strncmp(tmp->token, "export") ||
        !ft_strncmp(tmp->token, "unset") || !ft_strncmp(tmp->token, "env") ||
        !ft_strncmp(tmp->token, "exit"))
    {
        head->is_builtin = 1;
        printf("IS BUILTIN------->>> %s\n", tmp->token);
    }
    else
        head->is_builtin = 0;
}
