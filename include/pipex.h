/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:37:40 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/03 18:29:49 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

typedef struct s_pipex
{
	t_pos		*garbage;
	int			fdin;
	int			fdout;
	int			*childid;
	char		**env;
	char		**argv;
	int			argc;
}	t_pipex;

char	*ft_getpathline(char **env);
char	**ft_getpath(t_pipex *pipex, char **env);
void	ft_executesimple(t_pipex *pipex,
			char *cmdfile, char **cmd, char *error);
void	ft_execute(t_pipex *pipex, char *argv, char **env);
int		ft_closevaria(int i, ...);
int		*ft_child(t_pipex *pipex, int i, int *prevpipe, int *childid);
int		ft_close(int fd);
void	ft_executechild(t_pipex *pipex, int *prevpipe, int *newpipe, int i);
char	**ft_checkarg(char **argv, t_pipex *pipex);
char	**ft_getcmd(t_pipex *pipex, char *cmd);

#endif
