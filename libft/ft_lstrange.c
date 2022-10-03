/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:07:02 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 16:23:04 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstrange(t_list *list)
{
	t_list	*mem;
	int		nbr;

	nbr = 0;
	mem = list->pos->start;
	while (list != mem)
	{
		nbr++;
		mem = mem->next;
	}
	return (nbr);
}
