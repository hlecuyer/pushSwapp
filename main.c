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

int	file_stack(t_lst *stack, char **argv, int n)
{
	int i;
	int num;

	i = 0;

	while (i + 1 < n) {

		if (!is_number(argv[i + 1])) {
			return 0;
		}

		num = ft_atoi(argv[i + 1]);
		ft_atom_lst_pushend(stack, ft_atom_new(&num, sizeof(int)));
		i++;
	}
	return n;
}

t_lst *prepare_list(char **argv, int n)
{
	t_lst *stack;

	stack = ft_atom_lst_new(NULL);
	if(!file_stack(stack, argv, n))
	{
		ft_putstr("ERROR\n");
		return NULL;
	}
	return stack;
}

void put_atom(void *content)
{
	ft_putstr("'+++++++++\n'");
	ft_putnbr(*(int*)content);
	ft_putstr("'+++++++++\n'");
}

void cpy_tab(int *tab_a, int *tab_b, int start, int end)
{
	int i;

	i = 0;
	while (start < end)
	{
		tab_b[i] = tab_a[start];
		start++;
		i++;
	}
}

int	is_sort(int *tab, size_t len)
{
	int i;

	i = 0;
	while(i < (int)len - 1)
	{
		if (tab[i] > tab[i + 1])
			return 0;
		i++;
	}
	return 1;
}

int sort_small_tab(int *tab, size_t len)
{
	int i;
	int swap;

	i = 0;
	if (len == 1)
		return 0;
	if(!is_sort(tab, len)) {
		swap = tab[i + 1];
		tab[i + 1] = tab[i];
		tab[i] = swap;
		return 1;
	}
	else
		return 0;
}

void init_merge(t_merge *m, size_t len)
{
	m->half_b = len / 2;
	m->half_c = len / 2;
	if (len % 2 == 1)
		m->half_c++;
	m->ret = 0;
	m->i = 0;
	m->j = 0;
}

int* finish_fill(int *tab, int *tab_a,int i, int mid)
{
	while (i < mid)
	{
		*tab = tab_a[i];
		tab++;
		i++;
	}
	return tab;
}

int merge(int *tab, int *tab_b, int *tab_c, size_t len)
{
	t_merge var;

	init_merge(&var, len);
	while (var.i < var.half_b && var.j < var.half_c)
	{
		if (tab_b[var.i] < tab_c[var.j])
		{
			*tab = tab_b[var.i];
			var.i++;
		}
		else
		{
			*tab = tab_c[var.j];
			var.j++;
			var.ret += var.half_b - var.i;
		}
		tab++;
	}
	tab = finish_fill(tab, tab_b, var.i, var.half_b);
	tab = finish_fill(tab, tab_c, var.j, var.half_c);
	return var.ret;
}

t_inver* init_inversion(t_inver *v, int *tab, size_t len)
{
	v->half_a = len / 2;
	v->half_b = len / 2;
	if (v->half_a % 2 == 1)
		v->half_b++;
	v->tab_a = (int*)malloc(sizeof(int) * v->half_a);
	v->tab_b = (int*)malloc(sizeof(int) * v->half_b);
	if (v->tab_a == NULL || v->tab_b == NULL)
		return NULL;
	cpy_tab(tab, v->tab_a, 0, len / 2);
	cpy_tab(tab, v->tab_b, len / 2, len);
	v->ret = 0;
	return v;
}


int	inversion(int *tab, size_t len)
{
	t_inver var;

	init_inversion(&var, tab, len);
	var.ret += inversion(var.tab_a, var.half_a);
	// var.ret += inversion(var.tab_b, var.half_b);
	var.ret += merge(tab, var.tab_a, var.tab_b, len);
	free(var.tab_a);
	free(var.tab_b);
	return var.ret;
}


int count_inversion(t_lst *stack_a)
{
	int *tab;
	int i;
	t_atom *el;

	i = 0;
	tab = (int*)malloc(sizeof(int) * stack_a->len);
	el = stack_a->first;
	while(i < (int)stack_a->len) {
		tab[i] = *(int*)el->content;
		el = el->next;
		i++;
	}
	i = inversion(tab, stack_a->len);
	return i;
}

int start(t_lst *stack_a)
{
	t_lst *stack_b;
	int i;
	// int inversion;

	i = count_inversion(stack_a);
	ft_putnbr(i);
	ft_putstr("   yoloswag\n");
	stack_b = ft_atom_lst_new(NULL);
	return 0;

}


int		main(int argc, char **argv)
{
	t_lst *list;

	list = prepare_list(argv, argc);
	if (list == NULL)
	{
		return 1;
	}
	if (start(list)) {
		ft_putstr("ERROR\n");
		return 1;
	}
	ft_atom_lst_iter(list, &put_atom);


	ft_putstr("\n");
	ft_putstr("OK\n");
	return 0;
}
