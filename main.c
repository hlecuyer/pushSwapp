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

t_swap *prepare_swap(t_swap *s, char **argv, int n)
{
	s->stk_a = ft_atom_lst_new(NULL);
	s->stk_b = ft_atom_lst_new(NULL);
	s->action = ft_atom_lst_new(NULL);
	if(!file_stack(s->stk_a, argv, n)
		|| s->stk_a == NULL
		|| s->stk_b == NULL
		|| s->action == NULL)
	{
		ft_putstr("ERROR\n");
		return NULL;
	}
	return s;
}

void put_atom_int(void *content)
{
	ft_putstr("'+\n'");
	ft_putnbr(*(int*)content);
	ft_putstr("'+\n'");
}

void put_atom_str(void *content)
{
	ft_putstr("'+\n'");
	ft_putstr((char*)content);
	ft_putstr("'+\n'");
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

void init_merge(t_merge *m)
{
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

int merge(int *tab, t_inver var)
{
	t_merge count;

	init_merge(&count);
	while (count.i < var.half_a && count.j < var.half_b)
	{
		if (var.tab_a[count.i] < var.tab_b[count.j])
		{
			*tab = var.tab_a[count.i];
			count.i++;
		}
		else
		{
			*tab = var.tab_b[count.j];
			count.j++;
			count.ret += var.half_a - count.i;
		}
		tab++;
	}
	tab = finish_fill(tab, var.tab_a, count.i, var.half_a);
	tab = finish_fill(tab, var.tab_b, count.j, var.half_b);
	return count.ret;
}

t_inver* init_inversion(t_inver *v, int *tab, size_t len)
{
	v->half_a = len / 2;
	v->half_b = len / 2;
	if (len % 2 == 1 && len != 1)
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

void swap_first_atom(t_lst *list)
{
	t_atom *atom_a;
	t_atom *atom_b;
	t_atom *atom_c;

	atom_b = list->first->next;
	atom_a = list->first;
	atom_c = list->first->next->next;

	atom_b->prev = list->last;
	atom_b->next = atom_a;
	atom_a->next = atom_c;
	atom_a->prev = atom_b;
	list->first = atom_b;
}

void rotate(t_lst *lst)
{
	t_atom *a;

	a = ft_atom_lst_pop(lst);
	ft_atom_lst_pushend(lst, a);
}

void reverse_rotate(t_lst *lst)
{
	t_atom *a;

	a = ft_atom_lst_popend(lst);
	ft_atom_lst_push(lst, a);
}

void ra(t_swap *s) {
	rotate(s->stk_a);
	ft_atom_lst_pushend(s->action, ft_atom_new("ra", sizeof(char) * 2));
}

void rb(t_swap *s) {
	rotate(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("rb", sizeof(char) * 2));
}

void rr(t_swap *s) {
	rotate(s->stk_a);
	rotate(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("rr", sizeof(char) * 2));
}

void rra(t_swap *s) {
	reverse_rotate(s->stk_a);
	ft_atom_lst_pushend(s->action, ft_atom_new("rra", sizeof(char) * 3));
}

void rrb(t_swap *s) {
	reverse_rotate(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("rrb", sizeof(char) * 3));
}

void rrr(t_swap *s) {
	reverse_rotate(s->stk_a);
	reverse_rotate(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("rrr", sizeof(char) * 3));
}


void pa(t_swap *s)
{
	ft_atom_lst_push(s->stk_b, ft_atom_lst_pop(s->stk_a));
	ft_atom_lst_pushend(s->action, ft_atom_new("pa", sizeof(char) * 2));
}

void pb(t_swap *s)
{
	ft_atom_lst_push(s->stk_a, ft_atom_lst_pop(s->stk_b));
	ft_atom_lst_pushend(s->action, ft_atom_new("pb", sizeof(char) * 2));
}

void sa(t_swap *s) {
	swap_first_atom(s->stk_a);
	ft_atom_lst_pushend(s->action, ft_atom_new("sa", sizeof(char) * 2));
}

void sb(t_swap *s) {
	swap_first_atom(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("sa", sizeof(char) * 2));
}

void ss(t_swap *s) {
	swap_first_atom(s->stk_a);
	swap_first_atom(s->stk_b);
	ft_atom_lst_pushend(s->action, ft_atom_new("ss", sizeof(char) * 2));
}

int	inversion(int *tab, size_t len)
{
	t_inver var;

	init_inversion(&var, tab, len);
	if (len <= 2) {
		int i = sort_small_tab(tab, len);
		printf("ret  => %d", i);
		return i;
	}
	else
	{
		var.ret += inversion(var.tab_a, var.half_a);
		var.ret += inversion(var.tab_b, var.half_b);
	}
	var.ret += merge(tab, var);
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

void	print_state(t_swap *s, char *str)
{
	printf("%s\n\n", str);
	printf("stack_a\n");
	ft_atom_lst_iter(s->stk_a, &put_atom_int);
	printf("stack_b\n");
	ft_atom_lst_iter(s->stk_b, &put_atom_int);
	printf("stack_b\n");
	ft_atom_lst_iter(s->action, &put_atom_str);
	printf("fin\n\n");
}


int start(t_swap *swap)
{
	int i;
	// int inversion;

	i = count_inversion(swap->stk_a);
	ft_putnbr(i);
	ft_putstr("   yoloswag\n");
	quick_sort(swap);
	return 0;

}


int		main(int argc, char **argv)
{
	t_swap swap;

	if (!prepare_swap(&swap, argv, argc))
	{
		return 1;
	}
	start(&swap);
	return 0;
}
