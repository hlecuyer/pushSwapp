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

typedef struct		s_merge
{
	int				i;
	int				j;
	int				ret;
}					t_merge;

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
}					t_swap;

typedef struct		s_part
{
	int				pivot;
	int				right;
	int				left;
	int				is_sort;
}					t_part;

void create_partition(t_swap *s);

#endif
