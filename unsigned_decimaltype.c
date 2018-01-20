/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_decimaltype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:51:36 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 17:45:48 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	ft_zmodifier(va_list ap, t_arg *arg, size_t type_len, int base)
{
	(*arg).typearg.szi = va_arg(ap, size_t);
	(*arg).stock = ft_uitoa_base((*arg).typearg.szi, base);
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}


static size_t	ft_jmodifier(va_list ap, t_arg *arg, size_t type_len, int base)
{
	(*arg).typearg.uim = va_arg(ap, uintmax_t);
	(*arg).stock = ft_uitoa_base((*arg).typearg.uim, base);
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}

static size_t	ft_hmodifier(va_list ap, t_arg *arg, size_t type_len, int base)
{
	if ((*arg).conv[1] == 'h')
	{
		(*arg).typearg.uc = (unsigned char)va_arg(ap, int);
		(*arg).stock = ft_uitoa_base((unsigned int)(*arg).typearg.uc, base);
	}
	else
	{
		(*arg).typearg.ushi = (unsigned short int)va_arg(ap, unsigned int);
		(*arg).stock = ft_uitoa_base((*arg).typearg.ushi, base);
	}
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}



static size_t	ft_lmodifier(va_list ap, t_arg *arg, size_t type_len, int base)
{
	if ((*arg).conv[1] == 'l' && (*arg).type != 'U' && (*arg).type != 'O')
	{
		(*arg).typearg.ulli = va_arg(ap, unsigned long long int);
		(*arg).stock = ft_uitoa_base((*arg).typearg.lli, base);
	}
	else
	{
		(*arg).typearg.uli = va_arg(ap, unsigned long int);
		(*arg).stock = ft_uitoa_base((*arg).typearg.li, base);
	}
	type_len = ft_strlen((*arg).stock);
	return (type_len);
}


size_t		ft_decimaluint(va_list ap, t_arg *arg, size_t type_len, int base)
{
	if ((*arg).conv[0] == 'l' || (*arg).type == 'U' || (*arg).type == 'O') 
		type_len = ft_lmodifier(ap, arg, type_len, base);
	else if ((*arg).conv[0] == 0)
	{
		(*arg).typearg.ui = va_arg(ap, unsigned int);
		(*arg).stock = ft_uitoa_base((*arg).typearg.ui, base);
		type_len = ft_strlen((*arg).stock);
	}
	else if ((*arg).conv[0] == 'h')
		type_len = ft_hmodifier(ap, arg, type_len, base);
	else if ((*arg).conv[0] == 'j')
		type_len = ft_jmodifier(ap, arg, type_len, base);
	else
		type_len = ft_zmodifier(ap, arg, type_len, base);
	if ((*arg).precision == 0 && (*arg).stock[0] == '0')
		type_len = 0;
	(*arg).flags[1] = 0;
	(*arg).flags[2] = 0;
	return (type_len);
}
