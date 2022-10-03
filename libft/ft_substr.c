/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:23:35 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 15:30:09 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_pos *free)
{
	char	*str;

	if (start > ft_strlen(s))
		return (ft_strdup("", free));
	while (start + len > ft_strlen(s))
		len--;
	str = ft_malloc(sizeof(char) * (len + 1), free);
	if (!(str))
		return (0);
	s = start + s;
	str[len] = 0;
	while (len > 0)
	{
		str[len - 1] = s[len - 1];
		len--;
	}
	return (str);
}
