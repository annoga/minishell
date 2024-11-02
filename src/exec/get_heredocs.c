/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:56:32 by anovoa            #+#    #+#             */
/*   Updated: 2024/11/02 21:27:42 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//static char *remove_quotes(char *word);
//static int	has_quotes(char *str);

static int	save_heredoc(int fd, int exp, char *word, t_env **tenv);
int	process_heredoc(t_file *current, t_env **tenv);

int	get_heredocs(t_cmd *cmd, t_env **tenv, int internal)
{
//	(void)cmd;
//	(void)tenv;

	int		status;
	t_file	*redir;

	status = 0;
	if (internal)
		return (0);
	while (cmd && status == 0)
	{
		redir = cmd->files;
		while (redir)
		{
			if (redir && redir->type == HEREDOC)
			{
				status = process_heredoc(redir, tenv);
				//printf("out proc_hd:%p\n", redir);
				if (!cmd->cmd)
				{
					if (clear_heredoc(redir) != 0)
						return (1);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (status);
}

int	process_heredoc(t_file *current, t_env **tenv)
{
	int		res;
	int		fd;
	int		quotes;
	char	*word;

	quotes = 0;
	if (clear_heredoc(current) != 0)
		return (1);
	//word = ft_strdup(current->name);
//	if (!word)
//		return (1);
	quotes = current->is_quoted; //has_quotes(current->name);
//	if (quotes)
//		word = remove_quotes(current->name);
	//else
	word = current->name;
	fd = open("/tmp/temp_heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//printf("fd:%d\n\n\n", fd);
	//printf("has_q:%d\n\n\n", quotes);
	res = save_heredoc(fd, !quotes, word, tenv);
	//free(word);
	close(fd);//safe
	fd = open("/tmp/temp_heredoc.txt", O_RDONLY);//safe
	//printf("fd:%d\n\n\n", fd);
	//if (quotes)//
		//free(word);
	if (res > 0)
		current->heredoc_fd = res;
	else
		return (res * res);
	return (0);
}

/*static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}*/

//void	*ft_memmove(void *dst, const void *src, size_t len);
/*static char *remove_quotes(char *word)
{
	char	*res;
	int		i;
	int		j;
	char	open_quote;

	i = 0;
	j = -1;
	open_quote = 0;
	res = ft_calloc(ft_strlen(word) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (word[++j])
	{
		if (!open_quote && isquote(word[j]))
			open_quote = word[j];
		else if (open_quote && open_quote == word[j])
			open_quote = 0;
		else
			res[i++] = word[j];
	}
	return (res);
}*/

/*static char	*expand(char *line, t_env **tenv)//
{
	(void)tenv;
	return (line);
}*/

static int	save_heredoc(int fd, int exp, char *word, t_env **tenv)
{
	char	*line;
//	char	*tmp;
	t_token	*token;
	t_token	*tmp;

	//printf("exp:%d\n\n\n", exp);
	if (fd == -1)
		return (1);
	while (1)//señales, ctrlD sale pero no exit
	{
		line = readline("> ");
		if (!line)//?? ej CtrlD
		{
			free(line);
			return(close(fd));
		}
		if (!ft_strcmp(line, word))
		{
			//printf("break hd\n");
			break ;
		}
		if (exp)
		{

			token = tokenizer(line, *tenv);
			free(line);
			token = expansor(token, tenv, 1, 0);
			while (token)
			{
				
				ft_putstr_fd(tmp->token, fd);
				tmp = tmp->next;
			}
			free_token(&token);
			tmp = NULL;
			ft_putchar_fd('\n', fd);
			//tmp = expand(line, tenv); 
			//free(line);
			//line = tmp;
		}
		else
		{
			ft_putendl_fd(line, fd);
			free(line);
		}
	}
	free(line);
	return (fd);
}

int	create_tmp_file()
{
	int	fd;

	fd = open("/tmp/temp_heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}
