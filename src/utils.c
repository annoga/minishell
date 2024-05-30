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
void *return_error(char *str)
{
    printf("%s\n", str);
    return (NULL);
}

// size_t	ft_strlcpy(char *dest, char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size < 1)
// 		return (ft_strlen(src));
// 	while (src[i] && 0 < size - 1)
// 	{
// 		dest[i] = src[i];
//         size--;
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (ft_strlen(src));
// }

char *ft_strndup(const char *s, size_t n)
{
    char *dup;

    dup = (char *)malloc(n + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, (char *)s, n + 1);
    return (dup);
}

void add_token(t_token **head, t_token *new)
{
    t_token *tmp;

    if(!*head)
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}


// t_token	*ft_lstnew(char *content)
// {
// 	t_token	*new;

// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->token = content;
//     check_token(new);
// 	new->next = NULL;
// 	return (new);
// }

// void check_token(t_token *head)
// {
//     check_builtin(head);
//     check_pipe_bonus(head);
//     check_redirect(head);
//     if(!head->is_builtin && !head->is_pipe && !head->is_redir && !head->is_bonus)
//         head->is_arg = 1;
//     else
//         head->is_arg = 0;
// }
// void check_pipe_bonus(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, "|"))
//     {
//         head->is_pipe = 1;
//         head->is_bonus = 0;
//     }
//     else if(!ft_strncmp(tmp->token, "||") || !ft_strncmp(tmp->token, "&&"))
//     {
//         head->is_pipe = 0;
//         head->is_bonus = 1;
//     }
//     else
//     {    
//         head->is_pipe = 0;
//         head->is_bonus = 0;
//     }
// }

// void check_redirect(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, ">") || !ft_strncmp(tmp->token, ">>") ||
//         !ft_strncmp(tmp->token, "<") || !ft_strncmp(tmp->token, "<<"))
//         head->is_redir = 1;
//     else
//         head->is_redir = 0;
// }

// void check_builtin(t_token *head)
// {
//     t_token *tmp;

//     tmp = head;
//     if(!ft_strncmp(tmp->token, "echo") || !ft_strncmp(tmp->token, "cd") ||
//         !ft_strncmp(tmp->token, "pwd") || !ft_strncmp(tmp->token, "export") ||
//         !ft_strncmp(tmp->token, "unset") || !ft_strncmp(tmp->token, "env") ||
//         !ft_strncmp(tmp->token, "exit"))
//         head->is_builtin = 1;
//     else
//         head->is_builtin = 0;
// }
