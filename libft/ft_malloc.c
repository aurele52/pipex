/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:32:19 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 19:14:22 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(int size, t_pos *free)
{
	void	*new;

	new = malloc(size);
	if (new == 0)
		return (0);
	if (free != 0)
	{
		free->end = ft_lstnew(new, free, 0);
		if (free->end == 0)
			return (0);
	}
	return (new);
}
