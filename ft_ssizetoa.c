/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:21:11 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 17:47:28 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_power(ssize_t n, int i)
{
	if (n >= 10 || n <= -10)
		return (ft_power(n / 10, i + 1));
	else
		return (i);
}

static void		ft_strnbr(char *str, int isneg, ssize_t n, int size)
{
	int		i;

	i = size + isneg;
	str[i--] = 0;
	if (n < 0)
	{
		while (n <= -10)
		{
			str[i--] = -(n % 10) + 48;
			n = n / 10;
		}
		str[i--] = -n + 48;
		str[i] = '-';
	}
	else
	{
		while (n >= 10)
		{
			str[i--] = (n % 10) + 48;
			n = n / 10;
		}
		str[i] = n + 48;
	}
}

char			*ft_ssizetoa(ssize_t n)
{
	char	*str;
	int		size;
	int		isneg;
	int		i;

	if (n < 0)
		isneg = 1;
	else
		isneg = 0;
	i = 1;
	size = ft_power(n, i);
	if (!(str = ft_strnew(size + isneg)))
		return (NULL);
	ft_strnbr(str, isneg, n, size);
	return (str);
}
