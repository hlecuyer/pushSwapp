/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlecuyer <hlecuyer@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:17:59 by hlecuyer           #+#    #+#            */
/*   Updated: 2016/01/14 13:12:47 by hlecuyer          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int is_number(char *num)
{
	int i;

	i = ft_strlen(num) - 1;
	while (i >= 0)
	{
		if (!ft_isdigit(num[i]))
			return 0;
		i--;
	}
	return 1;
}

int	file_stack(int *stack, char **argv, int n)
{
	int i;

	i = 0;

	while (i < n) {
		if (!is_number(argv[i + 1])) {
			return 0;
		}
		stack[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	return n;
}

int		main(int argc, char **argv)
{
	int	*stack_a;
	int	*stack_b;
	int n;

	n = argc - 1;
	stack_a = (int *)malloc(sizeof(int) * n);
	stack_b = (int *)malloc(sizeof(int) * n);
	if(!file_stack(stack_a, argv, n))
	{
		ft_putstr("ERROR\n");
		return 1;
	}
	int i = 0;
	while (i < n) {
		ft_putnbr(stack_a[i]);
		ft_putstr("\n");
		i++;
	}
	ft_putstr("\n");
	ft_putstr("OK\n");
}
