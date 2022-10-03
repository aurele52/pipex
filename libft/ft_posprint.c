/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/07/10 11:35:45 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_posprint(t_pos *pos)
{
	t_list	*list;
	int		*mem;

	if (pos->end != 0 && pos->start != 0)
	{
		list = pos->start;
		while (list != list->pos->end)
		{
			mem = list->content;
			ft_putnbr(*mem);
			write(1, "\n", 1);
			list = list->next;
		}
		mem = list->content;
		ft_putnbr(*mem);
		write(1, "\n", 1);
	}
}
