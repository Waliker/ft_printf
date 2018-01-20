/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wputchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelest <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:51:22 by ndelest           #+#    #+#             */
/*   Updated: 2018/01/20 16:59:09 by ndelest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libftprintf.h"

void	ft_putwchar(unsigned int a, int size)
{
	unsigned char	c;
	
	while (size > 0)
	{
		c = (unsigned char)(a >> (size - 1) * 8);
		write(1, &c, 1);
		size--;
	}
}

static int		ft_getchar(wint_t wi, unsigned int a, int size)
{
	int		j;
	int		i;
	int		count;

	j = 0;
	i = 0;
	count = (size * 8) - (size + 1);
	while (i < count)
	{
		if (i == 6 || i == 14 || i == 22)
			i = i + 2;
		if (wi & (1 << j))
			a = a | (1 << i);
		i++;
		j++;
	}
	return (a);
}

unsigned int	ft_itowchar(wint_t wi, size_t *len)
{
	unsigned int a;
	int			size;

	size = 1;
	if (wi > 65535)
	{
		a = 4034953344;
		size = 4;
	}
	else if (wi > 2047)
	{
		a = 14712960;
		size = 3;
	}
	else if (wi > 127)
	{
		a = 49280;
		size = 2;
	}
	else
		a = (unsigned int)wi;
	a = ft_getchar(wi, a, size);
	*len = size;
	return (a);
}