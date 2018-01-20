/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:15:33 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 18:04:39 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>	///////
#include <stdlib.h> //////

void	ft_argreset(t_arg *arg)
{
	if ((*arg).type != 's' && (*arg).type != 'c' && (*arg).type != 'C')
		ft_strdel(&(*arg).stock);
	(*arg).type = 0;
	(*arg).minfield = 0;
	(*arg).precision = -1;
	ft_memset((*arg).flags, 0, 6);
	ft_memset((*arg).conv, 0, 5);
	ft_memset((*arg).buffer, 0, BUFF_SIZE);
	(*arg).index = 0;
}


t_arg	ft_arginit()
{
	t_arg	arg;

	arg.type = 0;
	arg.minfield = 0;
	arg.precision = -1;
	ft_memset(arg.flags, 0, 6);
	ft_memset(arg.conv, 0, 5);
	ft_memset(arg.buffer, 0, BUFF_SIZE);
	arg.index = 0;
	arg.len = 0;
	return (arg);
}

void	ft_printbuffer(t_arg *arg)
{
	(*arg).len = (*arg).len + ft_strlen((*arg).buffer);
	ft_putstr((*arg).buffer);
	ft_memset((*arg).buffer, 0, BUFF_SIZE);
	(*arg).index = 0;
}

void	ft_putbuffer(t_arg *arg, char c)
{
	if ((*arg).index < BUFF_SIZE - 1)
		(*arg).buffer[(*arg).index++] = c;
	else
	{
		ft_printbuffer(arg);
		(*arg).buffer[(*arg).index++] = c;
	}
}

void	ft_fillflags(const char *format, int *i, t_arg *arg)
{	
	while (format[*i] == '#' || format[*i] == '+' || format[*i] == '-' ||
			format[*i] == '0' || format[*i] == ' ')
	{
		if (format[*i] == '#')
			(*arg).flags[0] = format[*i];
		else if (format[*i] == '+')
			(*arg).flags[1] = format[*i];
		else if (format[*i] == ' ')
			(*arg).flags[2] = format[*i];
		else if (format[*i] == '0')
			(*arg).flags[3] = format[*i];
		else if (format[*i] == '-')
			(*arg).flags[4] = format[*i];
		++(*i);
	}	
}

void	ft_fillfields(const char *format, int *i, t_arg *arg)
{
	if (format[*i] >= 49 && format[*i] <= 57)
	{
		(*arg).minfield = format[(*i)++] - 48;
		while (format[*i] >= 48 && format[*i] <= 57)
			(*arg).minfield = ((*arg).minfield * 10) + format[(*i)++] - 48;
	}
	if (format[*i] == 46)
	{
		(*arg).precision = 0;
		++(*i);
		while (format[*i] >= 48 && format[*i] <= 57)
			(*arg).precision = ((*arg).precision * 10) + format[(*i)++] - 48;
	}
}

void	ft_putfield(t_arg *arg, char c, size_t type_len, int opt)
{
	int		i;
	int		j;
	int		isneg;

	i = 0;
	isneg = 0;
	if ((*arg).flags[1] == '-')
		isneg = 1;
	if (opt == 1)
	{
		if ((*arg).precision > (int)type_len - isneg)
			j = (*arg).precision + isneg;
		else
			j = (int)type_len;
		if (isneg == 0 && ((*arg).flags[1] == '+' || (*arg).flags[2] == ' '))
			j++;
		while (i++ < ((*arg).minfield - j))
			ft_putbuffer(arg, c);
	}
	if (opt == 2)
	{
		i = -isneg;
		while (i++ < ((*arg).precision - (int)type_len))
			ft_putbuffer(arg, c);
	}
}

static void	ft_puthashtag(t_arg *arg)
{
	if ((*arg).stock[0] != '0' && ((*arg).type == 'x' || (*arg).type == 'X'))
	{
		ft_putbuffer(arg, '0');
		if ((*arg).type == 'x')
			ft_putbuffer(arg, 'x');
		else
			ft_putbuffer(arg, 'X');
	}
	else if ((*arg).type == 'o' || (*arg).type == 'O')
		ft_putbuffer(arg, '0');
}

void	ft_putflagsnb(t_arg *arg, int type_len)
{
	if ((*arg).flags[0] != 0 && ((*arg).type == 'o' || (*arg).type == 'O'))
		(*arg).minfield = (*arg).minfield - 1;
	if ((*arg).flags[0] != 0 && ((*arg).type == 'x' || (*arg).type == 'X'))
		(*arg).minfield = (*arg).minfield - 2;
	if ((*arg).minfield > 0 && (*arg).flags[4] != '-' && (((*arg).flags[3] 
					== '0' && (*arg).precision >= 0) || (*arg).flags[3] != '0'))
		ft_putfield(arg, ' ', type_len, 1);
	if ((*arg).flags[0] != 0)
		ft_puthashtag(arg);
	if ((*arg).flags[1] != 0)
		ft_putbuffer(arg, (*arg).flags[1]);
	else if ((*arg).flags[2] == ' ')
		ft_putbuffer(arg, ' ');
	if ((*arg).precision >= 0)
		ft_putfield(arg, '0', type_len, 2);
	else if ((*arg).flags[3] == '0' && (*arg).flags[4] != '-')
		ft_putfield(arg, '0', type_len, 1);
}

int		ft_fillconv(const char *format, int *i, t_arg *arg)
{
	int		j;

	j = 0;
	while (j < 3 && (format[*i] == 'h' || format[*i] == 'l' || 
				format[*i] == 'j' || format[*i] == 'z'))
		(*arg).conv[j++] = format[(*i)++];
	if (j > 2)
		return (0);
	if (((*arg).conv[0] == 'j' || (*arg).conv[0] == 'z') 
			&& ((*arg).conv[1] != 0))
		return (0);
	if ((*arg).conv[0] != 0 && (*arg).conv[1] != 0 && (*arg).conv[0] 
			!= (*arg).conv[1])
		return (0);
	return (1);
}

int		ft_argint(va_list ap, t_arg *arg)
{
	int		i;
	size_t	type_len;

	type_len = 0;
	i = 0;
	if ((*arg).type == 'd' || (*arg).type == 'i' || (*arg).type == 'D')
		type_len = ft_decimalint(ap, arg, type_len);
	else if ((*arg).type == 'u' || (*arg).type == 'U')
		type_len = ft_decimaluint(ap, arg, type_len, 10);
	else if ((*arg).type == 'X' || (*arg).type == 'x')
		type_len = ft_decimaluint(ap, arg, type_len, 16);
	else if((*arg).type == 'o' || (*arg).type == 'O')
		type_len = ft_decimaluint(ap, arg, type_len, 8);
	if ((*arg).stock[0] == '-')
	{
		(*arg).flags[1] = '-';
		i = 1;
	}
	if ((*arg).type == 'x')
		ft_strputlowercase((*arg).stock);
	ft_putflagsnb(arg, type_len);
	while (i < (int)type_len)
		ft_putbuffer(arg, (*arg).stock[i++]);
	if ((*arg).flags[4] == '-')
		ft_putfield(arg, ' ', type_len, 1);
	ft_printbuffer(arg);
	ft_argreset(arg);
	return (1);
}

size_t	ft_putflagstring(t_arg *arg, size_t type_len)
{
	int		i;

	i = 0;
	if ((*arg).precision > 0 && (*arg).precision < (int)type_len)
		type_len = (*arg).precision;
	if ((*arg).flags[4] == '-')
		while (i < (int)type_len)
			ft_putbuffer(arg, (*arg).stock[i++]);
	i = 0;
	while (i++ < (*arg).minfield - (int)type_len)
		ft_putbuffer(arg, ' ');
	return (type_len);
}

void	ft_putflagschar(t_arg *arg, size_t type_len)
{
	int	i;

	i = 0;
	if ((*arg).flags[4] != '-')
		while (i++ < (*arg).minfield - (int)type_len)
			ft_putbuffer(arg, ' ');
	ft_printbuffer(arg);
	(*arg).len = (*arg).len + (int)type_len;
}

int		ft_argstring(va_list ap, t_arg *arg)
{
	int		i;
	size_t	type_len;

	type_len = 0;
	i = 0;
	if ((*arg).type == 's')
		(*arg).stock = (char *)va_arg(ap, char *);
	if ((*arg).stock == NULL)
		(*arg).stock = "(null)";
	type_len = ft_strlen((*arg).stock);
	type_len = ft_putflagstring(arg, type_len);
	if ((*arg).flags[4] != '-')
		while (i < (int)type_len)
			ft_putbuffer(arg, (*arg).stock[i++]);
	ft_printbuffer(arg);
	ft_argreset(arg);
	return (1);
}

int		ft_argchar(va_list ap, t_arg *arg)
{
	unsigned int	a;
	size_t			type_len;

	type_len = 1;
	if ((*arg).type == 'C' || ((*arg).conv[1] == 0 && (*arg).conv[0] == 'l'))
	{
		(*arg).typearg.wc = va_arg(ap, wint_t);
		a = ft_itowchar((*arg).typearg.wc, &type_len);
		ft_putflagschar(arg, type_len);
		ft_putwchar(a, (int)type_len);
	}
	else
	{

		(*arg).typearg.c = (char)va_arg(ap, int);
		ft_putflagschar(arg, type_len);
		ft_putchar((*arg).typearg.c);
	}
	if ((*arg).flags[4] == '-')
		while ((int)type_len < (*arg).minfield--)
			ft_putbuffer(arg, ' ');
	ft_printbuffer(arg);
	ft_argreset(arg);
	return (1);
}

int		ft_checkconv(va_list ap, t_arg *arg)
{
	int		a;

	a = 1;
	if ((*arg).type == 's')
		a = ft_argstring(ap, arg);
	else if ((*arg).type == 'c' || (*arg).type == 'C')
		a = ft_argchar(ap, arg);
	else if ((*arg).type == 'c' || (*arg).type == 'S' 
			|| (*arg).type =='p' || (*arg).type == 'C')
		return (a);
	else
		a = ft_argint(ap, arg);
	/*	if ((*arg).conv[a] == 'j')
		arg = ft_volatilearg(ap, arg);
		if ((*arg).conv[a] == 'z')
		arg = ft_sizetarg(ap, arg);
		if ((*arg).conv[a] == 'l' && (*arg).conv[a + 1] == 'l')
		arg = ft_longlongarg(ap, arg);
		if ((*arg).conv[a] == 'h' && (*arg).conv[a + 1] == 'h')
		arg = ft_chararg(ap, arg);
		if ((*arg).conv[a] == 'h')
		arg = ft_shortarg(ap, arg);
		else
		arg = ft_longwarg(ap, arg);*/
	return (a);
}

int 	ft_fillarg(const char *format, va_list ap, int *i, t_arg *arg)
{
	ft_fillflags(format, i, arg);
	ft_fillfields(format, i, arg);
	if (!ft_fillconv(format, i, arg))
		return (0);
	if (format[*i] == 's' || format[*i] == 'S' || format[*i] == 'p' || 
			format[*i] == 'd' || format[*i] == 'D' || format[*i] == 'i' || 
			format[*i] == 'o' || format[*i] == 'O' || format[*i] == 'u' ||
			format[*i] == 'U' || format[*i] == 'x' || format[*i] == 'X' ||
			format[*i] == 'c' || format[*i] == 'C')
		(*arg).type = format[*i];
	else
		return (0);
	ft_checkconv(ap, arg);
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	t_arg	arg;

	arg = ft_arginit();
	va_start(ap, format);
	i = 0;
	while (format[i] != 0)
	{
		if (format[i] != 37)
			ft_putbuffer(&arg, format[i++]);
		else
		{
			i++;
			if (!(ft_fillarg(format, ap, &i, &arg)))
				return (-1);
			i++;
		}
	}
	va_end(ap);
	ft_printbuffer(&arg);
	return (arg.len);
}