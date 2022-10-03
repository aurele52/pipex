/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:25:20 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/03 18:27:54 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_closevaria(int i, ...)
{
	va_list	param;
	int		fd;

	va_start(param, i);
	while (i > 0)
	{
		fd = va_arg(param, int);
		fd = close(fd);
		if (fd == -1)
			write(2, "n2p", 3);
		i--;
	}
	return (0);
}

int	ft_close(int fd)
{
	return (ft_closevaria(1, fd));
}

void	ft_executechild(t_pipex *pipex, int *prevpipe, int *newpipe, int i)
{		
	if (i == 0)
	{
		dup2(pipex->fdin, 0);
		ft_close(newpipe[0]);
		dup2(newpipe[1], 1);
		ft_closevaria(2, newpipe[1], pipex->fdin);
	}
	else if (i == pipex->argc - 4)
	{
		ft_closevaria(3, newpipe[0], newpipe[1], prevpipe[1]);
		dup2(prevpipe[0], 0);
		ft_close(prevpipe[0]);
		dup2(pipex->fdout, 1);
		ft_close(pipex->fdout);
	}
	else
	{
		ft_close(prevpipe[1]);
		dup2(prevpipe[0], 0);
		ft_closevaria(2, prevpipe[0], newpipe[0]);
		dup2(newpipe[1], 1);
		ft_closevaria(2, newpipe[1], pipex->fdout);
	}
	ft_execute(pipex, pipex->argv[i + 2], pipex->env);
}

int	*ft_child(t_pipex *pipex, int i, int *prevpipe, int *childid)
{
	int	*newpipe;

	newpipe = ft_malloc(sizeof(int) * 2, pipex->garbage);
	pipe(newpipe);
	childid[i] = fork();
	if (childid[i] == 0)
		ft_executechild(pipex, prevpipe, newpipe, i);
	else
	{
		if (i == 0)
			ft_close(pipex->fdin);
		else if (i == pipex->argc - 4)
		{
			ft_closevaria(3, pipex->fdout, newpipe[0], newpipe[1]);
			ft_closevaria(2, prevpipe[1], prevpipe[0]);
		}
		else
			ft_closevaria(2, prevpipe[1], prevpipe[0]);
	}
	return (newpipe);
}

char	**ft_checkarg(char **argv, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (argv[i])
		if (ft_strlen(argv[i++]) == 0)
			ft_exit(pipex->garbage,
				"arg empty, same as : parse error near `|'\n");
	return (argv);
}
