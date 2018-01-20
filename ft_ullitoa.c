/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:21:11 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/16 14:52:44 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_power(unsigned long long int n, int i)
{
	if (n >= 10)
		return (ft_power(n / 10, i + 1));
	else
		return (i);
}

static void		ft_strnbr(char *str, unsigned long long int n, int size)
{
	int		i;

	i = size;
	str[i--] = 0;
	while (n >= 10)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	str[i] = n + 48;
}

char			*ft_ullitoa(unsigned long long int n)
{
	char	*str;
	int		size;
	int		i;

	i = 1;
	size = ft_power(n, i);
	if (!(str = ft_strnew(size)))
		return (NULL);
	ft_strnbr(str, n, size);
	return (str);
}
