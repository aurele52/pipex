/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mallocint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:54:23 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 15:12:54 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mallocint(int i, t_pos *free)
{
	int	*ret;

	ret = ft_malloc(sizeof(ret), free);
	*ret = i;
	return (ret);
}
