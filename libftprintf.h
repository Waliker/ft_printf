/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:19:03 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 16:44:15 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <wchar.h>
#include "libft/includes/libft.h"

# define BUFF_SIZE 40096
typedef union				u_typearg
{
	int						i;
	short int				shi;
	long int				li;
	long long int			lli;
	intmax_t				im;
	ssize_t					sszi;
	unsigned int			ui;
	unsigned short int		ushi;
	unsigned long int		uli;
	unsigned long long int	ulli;
	uintmax_t				uim;
	unsigned char			uc;
	size_t					szi;
	char					c;
	wint_t					wc;
}							t_typearg;
typedef	struct	s_arg
{
	char		type;
	char		flags[5];
	char		conv[4];
	int			minfield;
	int			precision;
	char		buffer[BUFF_SIZE];
	int			index;
	int			len;
	char		*stock;
	t_typearg	typearg;
}				t_arg;
char	*ft_litoa(long int n);
char	*ft_ulitoa(unsigned long int n);
char	*ft_ullitoa(unsigned long long int n);
char	*ft_uimtoa(uintmax_t n);
int		ft_printf(const char *format, ...);
size_t	ft_decimalint(va_list ap, t_arg *arg, size_t type_len);
size_t	ft_decimaluint(va_list ap, t_arg *arg, size_t type_len, int base);
char	*ft_ssizetoa(ssize_t n);
char	*ft_imtoa(intmax_t n);
char			*ft_uitoa_base(uintmax_t n, int base);
void			ft_strputlowercase(char *str);
void	ft_putwchar(unsigned int a, int size);
unsigned int	ft_itowchar(wint_t wi, size_t *len);
#endif