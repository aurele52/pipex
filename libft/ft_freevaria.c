/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freevaria.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:36:02 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/21 17:38:04 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_freevaria(int i, ...)
{
	va_list	param;
	void	*p;

	va_start(param, i);
	while (i > 0)
	{
		p = va_arg(param, void *);
		free(p);
		i--;
	}
	return (0);
}
