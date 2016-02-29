/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlecuyer <hlecuyer@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:17:59 by hlecuyer           #+#    #+#            */
/*   Updated: 2016/01/14 13:12:47 by hlecuyer          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZP_STRUCT_H
# define ZP_STRUCT_H

typedef struct			s_action
{
	struct timeval		finish;
	int					type;
	int					lenght;
	char				buff[BUFF + 1];
	struct s_action		*next;
	struct s_action		*prev;
}
#endif
