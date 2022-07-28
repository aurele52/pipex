/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/07/27 12:17:35 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"

typedef struct s_pipex
{
	t_pos		*garbage;
	int			fdin;
	int			fdout;
	int	*childid;
	char	**env;
	char	**argv;
	int	argc;
}	t_pipex;


#endif
