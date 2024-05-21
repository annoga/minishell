/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovoa <anovoa@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:18:08 by anovoa            #+#    #+#             */
/*   Updated: 2023/12/20 18:01:50 by anovoa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

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

int	p_putchar(char c, t_params *p);
int	p_putstr(char *s, t_params *p);
int	count_digits(unsigned long n, int base);
int	set_padding(int size, t_params *p);
int	p_putnbr(unsigned int n, t_params *p);
int	p_puthex(unsigned int n, char *base, t_params *p);
int	p_putptr(unsigned long n, t_params *p);
int	put_left_blanks(t_params *p);
int	put_left_zeroes(t_params *p);
int	put_precision(t_params *p);
int	put_right_blanks(t_params *p);
int	solve_c(int c, t_params *p);
int	solve_percent(t_params *p);
int	solve_str(char *s, t_params *p);
int	solve_hex(unsigned int n, char *prefix, t_params *p);
int	solve_ptr(unsigned long ptr, t_params *p);
int	solve_nbr(long n, t_params *p);
int	ft_printf(const char *s, ...);

#endif
