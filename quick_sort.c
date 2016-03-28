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

void print_stacks(t_swap *s)
{
	t_atom *a;

	a = s->stk_a->first;
	ft_putstr("Stack A: ");
	while(a)
	{
		ft_putnbr(*(int*)a->content);
		a = a->next;
		ft_putstr(", ");
	}
	ft_putstr("\n");
	a = s->stk_b->first;
	ft_putstr("Stack B: ");
	while(a)
	{
		ft_putnbr(*(int*)a->content);
		a = a->next;
		ft_putstr(", ");
	}
	ft_putstr("\n");
}

void print_action(t_swap *s)
{
	t_atom *a;

	a = s->action->first;
	ft_putstr("Liste des actions: ");
	while(a)
	{
		ft_putstr((char*)a->content);
		a = a->next;
		ft_putstr(" - ");
	}
	ft_putstr("\n");
}

void print_partition(t_swap *s)
{
	t_atom *a;
	t_part *p;

	a = s->partition->first;
	ft_putstr("Partition : \n");
	while(a)
	{
		p = (t_part*)a->content;
		ft_putstr("partition len: ");
		ft_putnbr(p->len);
		ft_putstr("\npartition left: ");
		ft_putnbr(p->left);
		ft_putstr("\npartition right: ");
		ft_putnbr(p->right);
		if (p->pivot)
		{
			ft_putstr("\npartition pivot: ");
			ft_putnbr(p->right);
		}
		ft_putstr("\n******************\n");
		a = a->next;
	}
}


bool		is_sort_stk(t_lst *list)
{
	t_atom	*atom;
	//TODO optimiser et check partition plutot
	atom = list->first;
	while (atom->next != NULL)
	{
		if (*(int*)atom->content > *(int*)atom->next->content)
			return (false);
		atom = atom->next;
	}
	return (true);
}

void	init_part(t_swap *s)
{
	t_part p;
	t_atom *atom;

	p.pivot = *(int*)s->stk_a->first->content;
	p.right = s->stk_a->len - 1;
	p.left = 0;
	p.is_sort = false;
	p.index_right = s->stk_a->len - 1;
	p.index_left = 0;
	p.index_pivot = 0;
	p.len = s->stk_a->len;
	if ((atom = ft_atom_new(&p, sizeof(t_part))))
		s->partition = ft_atom_lst_new(atom);
}




void	push_from_partition(t_swap *s, t_atom *partition)
{
	t_atom	*stk;
	t_part	*part_content;
	int		i;

	i = 0;
	pb(s);
	part_content = (t_part*)partition->content;
	stk = s->stk_b->first;
	part_content->pivot = *(int*)stk->content;
	print_action(s);
	print_stacks(s);
	while (i < part_content->len - 1)
	{
		stk = s->stk_a->first;
		if (part_content->pivot < *(int*)stk->content)
		{
			pb(s);
			rb(s);
		}
		else
			ra(s);
		i++;
	}
}

void	rotate_a_x_time(t_swap *s, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ra(s);
		i++;
	}
}

void 	left_rotate(t_swap *s, int size, bool *ret)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ra(s);
		if (*(int*)s->stk_a->first->content < *(int*)s->stk_a->last->content)
		*ret = false;
		i++;
	}
}

void	right_rotate(t_swap *s, int size, bool *ret)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (s->stk_a->last->content && *(int*)s->stk_b->first->content < *(int*)s->stk_a->last->content)
			ret = false;
		pa(s);
		ra(s);
		i++;
	}
}

bool reorder_and_check_is_sort(t_swap *s, t_part *partition)
{
	bool	ret;
	int		i;

	ret = true;
	i = 0;
	if (partition->left > 1)
		left_rotate(s, partition->left, &ret);
	else if (partition->left == 1)
		ra(s);
	right_rotate(s, partition->right, &ret);
	return (ret);
}

void	treat_partitions(t_swap *s)
{
	t_atom	*partition;
	t_part	*partition_content;

	partition = s->partition->first;
	while (partition)
	{
		partition_content = (t_part*)partition->content;
		if (!partition_content->is_sort)
			push_from_partition(s, partition);
		else
			rotate_a_x_time(s, partition_content->len);
		print_partition(s);
		print_action(s);
		partition = partition->next;
	}

	partition = s->partition->first;
	while (partition)
	{
		partition_content = (t_part*)partition->content;
		if (partition_content->is_sort)
			rotate_a_x_time(s, partition_content->len);
		else
			partition_content->is_sort = reorder_and_check_is_sort(s, partition_content);
		partition = partition->next;
	}
}

bool	is_sort_part(t_lst *stk_a, t_atom *partition_atom)
{
	int		i;
	t_atom	*atom;
	t_part	*partition;

	i = 0;
	partition = (t_part*)partition_atom->content;
	atom = stk_a->first;
	if (partition->len == 1)
		return (true);
	while (i < partition->index_left)
	{
		atom = atom->next;
		i++;
	}
	while (i < partition->index_right)
	{
		if (*(int*)atom->content > *(int*)atom->next->content)
			return (false);
		atom = atom->next;
		i++;
	}
	return (true);
}

t_atom	*new_partition(int len)
{
	t_part new_partition;

	new_partition.len = len;
	new_partition.right = len - 1;
	new_partition.left = 0;
	return (ft_atom_new(&new_partition, sizeof(t_part)));
}


void divide_partition(t_swap *s, t_atom *partition, t_lst *new_part)
{
	t_part	*tmp;
	t_atom	*new_right;
	t_atom	*new_left;

	tmp = (t_part*)partition->content;
	new_right = new_partition(tmp->right);
	new_left = new_partition(tmp->left);
	if (!new_left || !new_right)
		return ;
	tmp->len = 1;
	tmp->is_sort = true;
	ft_atom_lst_pushend(new_part, new_left);
	ft_atom_lst_pushend(new_part, ft_atom_lst_pop(s->partition));
	ft_atom_lst_pushend(new_part, new_right);
}

bool	create_partition(t_swap *s)
{
	t_atom	*partition;
	t_atom	*partition_next;
	t_part	*part_content;
	t_lst	*new_part;

	partition = s->partition->first;
	if ((new_part = ft_atom_lst_new(NULL)))
		return (false);
	while (partition)
	{
		partition_next = partition->next;
		part_content = (t_part*)partition->content;
		if (part_content->is_sort || !is_sort_part(s->stk_a, partition))
			divide_partition(s, partition, new_part);
		else
		{
			part_content->is_sort = true;
			ft_atom_lst_pushend(new_part, ft_atom_lst_pop(s->partition));
		}
		partition = partition_next;
	}
	free(s->partition);
	s->partition = new_part;
	return (true);
}

void	quick_sort(t_swap *s)
{
	init_part(s);
	print_stacks(s);
	while(!is_sort_stk(s->stk_a))
	{
		treat_partitions(s);
		create_partition(s);
	}
	print_stacks(s);
	print_action(s);
	printf("yoloswag tout va bien\n");
}
