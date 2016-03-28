/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlecuyer <hlecuyer@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:17:59 by hlecuyer           #+#    #+#            */
/*   Updated: 2016/01/14 13:12:47 by hlecuyer          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_merge	t_merge;

struct		s_merge
{
	int32_t		i;
	int		j;
	int		ret;
};

typedef struct		s_inver
{
	int				*tab_a;
	int				*tab_b;
	int				half_a;
	int				half_b;
	int				ret;
}					t_inver;

typedef struct		s_swap
{
	t_lst			*stk_a;
	t_lst			*stk_b;
	t_lst			*action;
	t_lst			*partition;
}					t_swap;

typedef struct		s_part
{
	int				pivot;
	int				right;
	int				left;
	int				index_pivot;
	int				index_right;
	int				index_left;
	int				len;
	bool			is_sort;
}					t_part;

bool 				create_partition(t_swap *s);

int					count_inversion(t_lst *stack_a);

int					is_sort(int *tab, size_t len);
int					merge(int *tab, t_inver var);

void				quick_sort(t_swap *s);

void ra(t_swap *s);
void rb(t_swap *s);
void rr(t_swap *s);
void rra(t_swap *s);
void rrb(t_swap *s);
void rrr(t_swap *s);
void pa(t_swap *s);
void pb(t_swap *s);
void sa(t_swap *s);
void sb(t_swap *s);
void ss(t_swap *s);



#endif
