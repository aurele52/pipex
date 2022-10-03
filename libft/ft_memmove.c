/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 01:33:59 by audreyer          #+#    #+#             */
/*   Updated: 2021/11/29 20:57:10 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*destination;

	source = (char *)src;
	destination = (char *)dest;
	if (src < dest && src + n >= dest)
	{
		while (n--)
			destination[n] = source[n];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
