/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmedian.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:07:46 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 21:29:30 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmedian(t_pos *pos)
{
	t_list	*medianpot;
	t_list	*mem;
	int		nbr;

	medianpot = pos->start;
	while (1)
	{
		nbr = 0;
		mem = pos->start;
		while (mem != pos->end && nbr < *pos->size / 2 + 1)
		{
			if (ft_voidtoint(mem->content) > ft_voidtoint(medianpot->content))
				nbr++;
			mem = mem->next;
		}
		if (ft_voidtoint(mem->content) > ft_voidtoint(medianpot->content))
			nbr++;
		if ((nbr == *pos->size / 2 && *pos->size % 2 == 1)
			|| ((nbr == *pos->size / 2 - 1
					|| nbr == *pos->size / 2)
				&& *pos->size % 2 == 0))
			return (medianpot);
		medianpot = medianpot->next;
	}
	return (0);
}
