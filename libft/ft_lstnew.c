/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:58:02 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 14:53:22 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, t_pos *pos, t_pos *free)
{
	t_list	*liste;

	liste = ft_malloc(sizeof(*liste), free);
	if (liste == 0)
		return (0);
	liste->content = content;
	liste->pos = pos;
	*liste->pos->size = *liste->pos->size + 1;
	if (pos->end == 0 || pos->start == 0)
	{
		liste->next = liste;
		liste->back = liste;
		pos->start = liste;
		pos->end = liste;
	}
	else
	{
		liste->next = pos->start;
		liste->back = pos->end;
		pos->start->back = liste;
		pos->end->next = liste;
	}
	return (liste);
}
