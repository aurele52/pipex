/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:18:05 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/03 18:25:07 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

int	ft_heredoc(t_pipex *pipex, char *limiter)
{
	int		fd;
	char	*str;

	str = 0;
	limiter = ft_strjoin(limiter, "\n", pipex->garbage);
	if (!access("heredoc_tmp", F_OK))
		unlink("heredoc_tmp");
	fd = open("heredoc_tmp", O_CREAT | O_RDWR, 0777);
	while (ft_strcmp(str, limiter) != 0)
	{
		write(0, ">", 1);
		str = get_next_line(0, pipex->garbage);
		if (str == 0)
			ft_exit(pipex->garbage, "\nheredoc error");
		if (ft_strcmp(str, limiter) != 0)
			write(fd, str, ft_strlen(str));
	}
	ft_closevaria(1, fd);
	fd = open("heredoc_tmp", O_RDONLY);
	return (fd);
}

void	ft_pipexinit2(int argc, char **argv, char **env, t_pipex *pipex)
{
	pipex->env = env;
	pipex->argc = argc;
	pipex->argv = ft_checkarg(argv, pipex);
	if (ft_strcmp(argv[1], "HERE_DOC") == 0)
	{
		pipex->fdin = ft_heredoc(pipex, argv[2]);
		pipex->argv = &pipex->argv[1];
		pipex->argc = pipex->argc - 1;
	}
	else
		pipex->fdin = open(argv[1], O_RDONLY, 0777);
	if (pipex->fdin == -1)
		ft_exit(pipex->garbage, "fail open");
	pipex->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->fdout == -1)
	{
		close(pipex->fdin);
		ft_exit(pipex->garbage, "fail open");
	}
}

t_pipex	*ft_pipexinit(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	t_pos	*garbage;

	garbage = ft_setpos(0);
	if (!garbage)
		ft_exit(0, "fail malloc");
	pipex = ft_malloc(sizeof(*pipex), garbage);
	if (!pipex)
		ft_exit(garbage, "fail malloc");
	pipex->childid = ft_malloc(sizeof(int) * (argc - 3), garbage);
	if (!pipex->childid)
		ft_exit(garbage, "fail malloc");
	pipex->garbage = garbage;
	ft_pipexinit2(argc, argv, env, pipex);
	return (pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		*mypipe;
	int		i;

	i = 0;
	if (argc < 5)
		return (0);
	pipex = ft_pipexinit(argc, argv, env);
	mypipe = 0;
	while (i < pipex->argc - 3)
	{
		mypipe = ft_child(pipex, i, mypipe, pipex->childid);
		i++;
	}
	while (i-- > 0)
		waitpid(pipex->childid[i], 0, 0);
	ft_exit(pipex->garbage, 0);
}
