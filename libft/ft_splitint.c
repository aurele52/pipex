/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:34:34 by audreyer          #+#    #+#             */
/*   Updated: 2022/07/19 04:42:20 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_linecount(char const **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_spacenbr(char const *s)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (s[i] != 0)
	{
		if ((s[i] <= '9' && s[i] >= '0')
			&& (i == 0 || (s[i - 1] < '0' || s[i - 1] > '9')))
			nbr++;
		i++;
	}
	return (nbr);
}

static int	*ft_makeline(char const *s, t_pos *free)
{
	int	i;
	int	a;
	int	*str;
	int	spacenbr;

	a = 0;
	spacenbr = ft_spacenbr(s);
	i = 0;
	str = ft_malloc((sizeof(int) * (spacenbr + 1)), free);
	if (!str)
		return (0);
	while (s[i] != 0)
	{
		str[a++] = ft_atoi(&s[i]);
		while (s[i] != ' ' && s[i] != 0)
			i++;
		while (s[i] == ' ')
			i++;
	}
	return (str);
}

void	ft_print(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		write(1, &tab[i], ft_strlen(tab[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	**ft_splitint(char *s, t_pos *free)
{
	char	**split;
	int		**str;
	int		line;
	int		i;

	i = 0;
	split = ft_split(s, '\n', free);
	if (split == 0)
		return (0);
	line = ft_linecount((const char **)split);
	str = ft_malloc((sizeof(int *) * (line + 1)), free);
	if (!str)
		return (0);
	str[line] = 0;
	while (i != line)
	{
		str[i] = ft_makeline(split[i], free);
		i++;
	}
	return (str);
}
