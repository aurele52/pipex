/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:08:00 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 19:39:39 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *list, int freee)
{
	if (freee == 1)
		free(list->content);
	*list->pos->size = *list->pos->size - 1;
	if (list->pos->end == list->pos->start)
	{
		list->pos->end = 0;
		list->pos->start = 0;
	}
	else
	{
		if (list->pos->end == list)
			list->pos->end = list->back;
		if (list->pos->start == list)
			list->pos->start = list->next;
		list->back->next = list->next;
		list->next->back = list->back;
	}
	if (freee != 0)
		free(list);
}
