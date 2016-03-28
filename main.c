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

#include "push_swap.h"

void put_atom_int(void *content)
{
	ft_putstr("'+\n'");
	ft_putnbr(*(int*)content);
	ft_putstr("'+\n'");
}

void 	start(t_swap *swap)
{
	int i;

	i = count_inversion(swap->stk_a);
	ft_putnbr(i);
	ft_putstr("   yoloswag\n");
	quick_sort(swap);
	// return 0;
	ft_atom_lst_iter(swap->stk_a, &put_atom_int);
}

bool 	is_number(char *num)
{
	char	*it;
	bool	check;

	it = num;
	check = false;
	if (*it != 0 && *it == '-')
		++it;
	while (*it != 0)
	{
		if (ft_isdigit(*it))
			check = true;
		else
			return (false);
		++it;
	}
	return (check);
}

bool	parse_args(t_lst *stack, char **argv)
{
	int		num;
	t_atom	*new_atom;

	while (*argv != NULL)
	{
		if (is_number(*argv))
		{
			num = ft_atoi(*argv);
			new_atom = ft_atom_new(&num, sizeof(int));
			if (new_atom)
				ft_atom_lst_pushend(stack, new_atom);
		}
		else
			return (false);
		++argv;
	}
	return (true);
}

bool 	init_swap(t_swap *swap)
{
	swap->stk_a = ft_atom_lst_new(NULL);
	swap->stk_b = ft_atom_lst_new(NULL);
	swap->action = ft_atom_lst_new(NULL);
	swap->old_part = ft_atom_lst_new(NULL);
	swap->new_part = ft_atom_lst_new(NULL);
	return (swap->stk_a && swap->stk_b
			&& swap->action && swap->old_part && swap->new_part);
}

// WIP
// static void clear_swap(t_swap *swap)
// {
// 	if (swap->stk_a != NULL)
// 		ft_atom_lst_del(swap->stk_a, );
// }

int		main(int argc, char **argv)
{
	t_swap swap;

	if (argc < 2)
		ft_putendl_fd("NOPE", 2);
	else
	{
		if (init_swap(&swap) == true
			&& parse_args(swap.stk_a, argv + 1) == true)
			start(&swap);
		// clear_swap(&swap);
	}
	return (0);
}
