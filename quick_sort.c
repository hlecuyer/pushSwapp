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
#include "push_swap.h"
#include <stdio.h>

int		is_sort_stk(t_lst list)
{
	t_atom atom;

	atom = list->first;
	while (atom->next != NULL)
	{
		if (*(int*)atom->content > *(int)atom->next->content))
			return 0;
		atom = atom->next;
	}
}

void init_part(t_swap s)
{
	t_part p;

	p.pivot = *(int*)s->stk_a->first->content;
	p.right = s->stk_a->len;
	p.left = 0;
	p.is_sort = 0;
	ft_atom_lst_new(ft_atom_new(p, sizeof(t_part)));
}



void divide_partition(t_swap s, t_atom partition)
{
	typedef
	 MyCustomType;

}

void create_partition(t_swap *s)
{
	t_atom atom;

	if (s->part == null)
	{
		s->part = init_part(s);
	}
	else
	{
		atom = s->part->first;
		while (atom)
		{
			if (!is_sort_part(s, atom))
			{
				divide_partition(s, atom);
			}
			else
				atom->content->is_sort = 1;
			atom = atom->next;
		}
	}
}


void	quick_sort(t_swap *s)
{
	if (!is_sort_stk(s->stk_a))
		return 1;
	create_partition(s);
}
