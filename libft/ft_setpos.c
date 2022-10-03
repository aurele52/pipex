/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:38:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/23 17:32:14 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pos	*ft_setpos(t_pos *free)
{
	t_pos	*pos;
	int		*size;

	size = ft_malloc(sizeof(*size), free);
	if (size == 0)
		return (0);
	pos = ft_malloc(sizeof(*pos), free);
	if (pos == 0)
	{
		if (free == 0)
			ft_freevaria(1, size);
		return (0);
	}
	pos->end = 0;
	pos->size = size;
	pos->start = 0;
	*size = 0;
	return (pos);
}
