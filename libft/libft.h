/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:11:12 by anovoa            #+#    #+#             */
/*   Updated: 2024/08/15 20:51:32 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# define MAX_FD 1024
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_params
{
	int		reset;
	int		max;
	int		dot;
	int		bdot;
	int		neg;
	int		prefx;
	char	sign;
	int		zero;
	char	fill;	
	char	type;	
	int		wc;
}	t_params;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

/* libft */
int				ft_isalpha(int c);
int				ft_toupper(int c);
int				ft_isdigit(int c);
int				ft_tolower(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_atoi(const char *str);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
size_t			ft_strlcat(char *dest, char *src, size_t size);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);



/* ft_printf */
size_t			ft_countwords(char const *str, char c);
int				p_putchar(char c, t_params *p);
int				p_putstr(char *s, t_params *p);
int				count_digits_base(unsigned long n, int base);
int				set_padding(int size, t_params *p);
int				p_putnbr(unsigned int n, t_params *p);
int				p_puthex(unsigned int n, char *base, t_params *p);
int				p_putptr(unsigned long n, t_params *p);
int				put_left_blanks(t_params *p);
int				put_left_zeroes(t_params *p);
int				put_precision(t_params *p);
int				put_right_blanks(t_params *p);
int				solve_c(int c, t_params *p);
int				solve_percent(t_params *p);
int				solve_str(char *s, t_params *p);
int				solve_hex(unsigned int n, char *prefix, t_params *p);
int				solve_ptr(unsigned long ptr, t_params *p);
int				solve_nbr(long n, t_params *p);
int				ft_printf(const char *s, ...);

/* get_next_line */
void			*ft_calloc(size_t count, size_t size);
void			*ft_reset(char **arg);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_putchar_fd(int c, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_putstr_fd(char *s, int fd);
char			*get_next_line(int fd);

/* fdf */
int				ft_atoi_base(const char *str, int str_base);
unsigned int	ft_atoui_base(const char *str, int str_base);
int				ft_countdigits_base(int n, int base);
int				ft_isspace(int c);
int				ft_issign(int c);
char			*ft_strnstr(const char *str, const char *needle, size_t len);
char			*get_whole_file(int fd);

/* minishell */
long			ft_atol(const char *str);

#endif
