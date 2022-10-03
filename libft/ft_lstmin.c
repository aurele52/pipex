/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:05:17 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 21:30:03 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmin(t_pos *pos)
{
	t_list	*min;
	t_list	*list;

	min = pos->start;
	list = pos->start->next;
	while (list != pos->start)
	{
		if (ft_voidtoint(min->content) > ft_voidtoint(list->content))
			min = list;
		list = list->next;
	}
	return (min);
}
