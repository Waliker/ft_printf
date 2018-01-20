/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_decimaltype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:51:36 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 17:16:41 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	ft_zmodifier(va_list ap, t_arg *arg, size_t type_len)
{
	(*arg).typearg.sszi = va_arg(ap, ssize_t);
	(*arg).stock = ft_ssizetoa((*arg).typearg.sszi);
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}


static size_t	ft_jmodifier(va_list ap, t_arg *arg, size_t type_len)
{
	(*arg).typearg.im = va_arg(ap, intmax_t);
	(*arg).stock = ft_imtoa((*arg).typearg.im);
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}

static size_t	ft_hmodifier(va_list ap, t_arg *arg, size_t type_len)
{
	if ((*arg).conv[1] == 'h')
	{
		(*arg).typearg.c = (char)va_arg(ap, int);
		(*arg).stock = ft_itoa((int)(*arg).typearg.c);
	}
	else
	{
		(*arg).typearg.shi = (short int)va_arg(ap, int);
		(*arg).stock = ft_itoa((*arg).typearg.shi);
	}
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}



static size_t	ft_lmodifier(va_list ap, t_arg *arg, size_t type_len)
{
	if ((*arg).conv[1] == 'l')
	{
		(*arg).typearg.lli = va_arg(ap, long long int);
		(*arg).stock = ft_litoa((*arg).typearg.lli);
	}
	else
	{
		(*arg).typearg.li = va_arg(ap, long int);
		(*arg).stock = ft_litoa((*arg).typearg.li);
	}
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}


size_t		ft_decimalint(va_list ap, t_arg *arg, size_t type_len)
{
	if ((*arg).conv[0] == 'l' || (*arg).type == 'D')
		type_len = ft_lmodifier(ap, arg, type_len);
	else if ((*arg).conv[0] == 0)
	{
		(*arg).typearg.i = va_arg(ap, int);
		(*arg).stock = ft_itoa((*arg).typearg.i);
		type_len = ft_strlen((*arg).stock);
	}
	else if ((*arg).conv[0] == 'h')
		type_len = ft_hmodifier(ap, arg, type_len);
	else if ((*arg).conv[0] == 'j')
		type_len = ft_jmodifier(ap, arg, type_len);
	else
		type_len = ft_zmodifier(ap, arg, type_len);
	if ((*arg).precision == 0 && (*arg).stock[0] == '0')
		type_len = 0;
	(*arg).flags[0] = 0;
	return (type_len);
}
