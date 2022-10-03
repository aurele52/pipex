/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setintzerovaria.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:41:53 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/22 00:42:30 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_setintzerovaria(int i, ...)
{
	va_list	param;
	int		*p;

	va_start(param, i);
	while (i > 0)
	{
		p = va_arg(param, int *);
		*p = 0;
		i--;
	}
}
