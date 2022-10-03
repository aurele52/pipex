/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:39:03 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/21 18:15:44 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_useless(int len, char const *s1)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (0);
	while (++i < len)
		str[i] = s1[i];
	str[i] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;

	while (ft_isset(*s1, set) == 1 && *s1)
		s1++;
	len = ft_strlen(s1) - 1;
	while (ft_isset(s1[len], set) == 1 && len > 0)
		len--;
	return (ft_useless(len + 1, s1));
}
