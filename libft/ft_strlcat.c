/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:12:56 by audreyer          #+#    #+#             */
/*   Updated: 2021/11/29 20:45:23 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	int		len;

	len = ft_strlen(dst);
	j = 0;
	if (size <= ft_strlen(dst))
		return (ft_strlen((char *)src) + size);
	while (src[j] && j + len < size - 1)
	{
		dst[j + len] = src[j];
		j++;
	}
	dst[j + len] = 0;
	if (size < (size_t)ft_strlen(dst))
		return (ft_strlen((char *)src) + size);
	else
		return (len + ft_strlen((char *)src));
}
