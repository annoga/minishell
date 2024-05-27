/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:34:44 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/05/27 17:10:34 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../inc/minishell.h"

char	*skip_separator(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}
int skip_redir_bonus(char c1, char c2, char *line)
{
	if (*line == c1)
	{
		line++;
		if (*line == c2)
			return (2);
		return (1);
	}
	return (0);
}

char	*skip_to_next_word(char *line)
{
	int	quote;

	quote = 0;
	if(skip_redir_bonus('<', '<', line) == 1 || skip_redir_bonus('>', '>', line) == 1 || skip_redir_bonus('|', '|', line) == 1 || skip_redir_bonus('&', '&', line) == 1)
		return (line + 1);
	if(skip_redir_bonus('<', '<', line) == 2 || skip_redir_bonus('>', '>', line) == 2 || skip_redir_bonus('|', '|', line) == 2 || skip_redir_bonus('&', '&', line) == 2)
		return (line + 2);
	if (*line == '\"' || *line == '\'')
		quote = *line++;
	if (quote == '\"')
		while (*line && *line != '\"')
			line++;
	else if (quote == '\'')
		while (*line && *line != '\'')
			line++;
	else
		while (*line && !ft_isspace(*line) && *line != '\'' && *line != '\"' && *line != '<' && *line != '>' && *line != '|' && *line != '&')
			line++;
	if (quote && (*line == '\'' || *line == '\"'))
		line++;
	return (line);
}

int	count_words(char *line)
{
	int	words;

	words = 0;
	while (*line)
	{
		line = skip_separator(line);
		if (!*line)
			return (words);
		words++;
		line = skip_to_next_word(line);
	}
	return (words);
}

char	*get_word(char **line)
{
	char	*word;
	char	*aux;
	int		len;
	int		i;

	*line = skip_separator(*line);
	aux = skip_to_next_word(*line);
	len = aux - *line;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	aux = *line;
	i = 0;
	while (i < len)
		word[i++] = *aux++;
	word[i] = '\0';
	*line = aux;
	return (word);
}

char	**split_line(
		char *line/*,
		char *(*skip_separators)(char *),
		char *(*next_word)(char *)*/
)
{
	char	**split;
	int		words;
	int		i;

	words = count_words(line);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
		split[i++] = get_word(&line);
	split[i] = NULL;
	return (split);
}

// int	main(int argc, char **argv)
// {
// 	char	**split;
// 	int		i;

// 	if (argc != 2)
// 		return (1);
// 	split = split_line(argv[1]);
// 	if (!split)
// 	{
// 		printf("Malloc Error\n");
// 		return (2);
// 	}
// 	printf("Line: \"%s\"\n\n", argv[1]);
// 	for (i = 0; split[i]; i++)
// 		printf("split[%d]: \"%s\"\n", i, split[i]);
// 	printf("split[%d]: \"%s\"\n", i, split[i]);
// }
