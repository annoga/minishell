#include "../../inc/minishell.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n1;
	size_t	n2;
	size_t	n;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	i = 0;
	if (n1 > n2)
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