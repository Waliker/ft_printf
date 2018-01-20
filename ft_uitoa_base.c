/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:21:11 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/18 16:49:35 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_power(uintmax_t n, int i, int base)
{
	if (n >= (uintmax_t)base)
		return (ft_power(n / base, i + 1, base));
	else
		return (i);
}

static void		ft_strnbr(char *str, uintmax_t n, int base, int i)
{
	i--;
	while (n >= (uintmax_t)base)
	{
		str[i--] = (n % base) + (n % base > 9 ? 'A' - 10 : 48);
		n = n / base;
	}
	str[i] = n + (n % base > 9 ? 'A' - 10 : 48);
}

char			*ft_uitoa_base(uintmax_t n, int base)
{
	char	*str;
	int		size;
	int		i;

	i = 1;
	size = ft_power(n, i, base);
	i = size;
	if (!(str = ft_strnew(i)))
		return (NULL);
	ft_strnbr(str, n, base, i);
	return (str);
}
