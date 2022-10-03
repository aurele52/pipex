/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:52:02 by audreyer          #+#    #+#             */
/*   Updated: 2022/06/20 18:10:36 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_unsplit(char **tab, char *charset, t_pos *free)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("", free);
	if (str == 0)
		return (0);
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i], free);
		if (str == 0)
			return (0);
		i++;
		if (tab[i] && charset != 0)
		{
			str = ft_strjoin(str, charset, free);
			if (str == 0)
				return (0);
		}
	}
	return (str);
}
