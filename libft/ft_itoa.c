/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 13:11:35 by mle-roy           #+#    #+#             */
/*   Updated: 2015/01/31 21:56:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_filltemp(char *temp, int *l, int n)
{
	char	c;

	while (n != 0)
	{
		if (n < 0)
			c = '0' - (n % 10);
		else
			c = (n % 10) + '0';
		temp[(*l)--] = c;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*newc;
	char	temp[11];
	int		l;
	int		neg;

	l = 10;
	neg = 0;
	ft_strcpy(temp, "00000000000");
	if (n == 0)
		l--;
	else
	{
		if (n < 0)
			neg = 1;
		ft_filltemp(temp, &l, n);
		if (neg == 1)
			temp[l--] = '-';
	}
	newc = ft_strsub(temp, (l + 1), ft_strlen(&temp[l]));
	return (newc);
}
