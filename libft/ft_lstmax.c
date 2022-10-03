/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:06:01 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 21:28:28 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmax(t_pos *pos)
{
	t_list	*max;
	t_list	*list;

	max = pos->start;
	list = pos->start->next;
	while (list != pos->start)
	{
		if (ft_voidtoint(max->content) < ft_voidtoint(list->content))
			max = list;
		list = list->next;
	}
	return (max);
}
