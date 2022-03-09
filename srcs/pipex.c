/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:18:05 by audreyer          #+#    #+#             */
/*   Updated: 2022/02/24 18:40:16 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getpathline(char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0 && (env[i][0] != 'P' || env[i][1] != 'A' || env[i][2] != 'T' || env[i][3] != 'H' || env[i][4] != '='))
		i++;
	if (env[i] == 0)
		return(0);
	return (&env[i][5]);
}

char	**ft_getpath(char **env, t_pos *free)
{
	char	*pathline;
	char	**pathtab;

	pathline = ft_getpathline(env);
	pathtab = ft_split(pathline, ':', free);
	return (pathtab);
}

char	**ft_getcmd(char *cmd, t_pos *free)
{
	return (ft_split(cmd, ' ', free));
}

int	ft_execute(char **argv, char **env, int	n ,t_pos *free)
{
	char	**pathtab;
	char	**cmd;
	int	i;
	
	i = 0;
	pathtab = ft_getpath(env, free);
	cmd = ft_getcmd(argv[n], free);
	if (cmd == 0|| pathtab == 0)
	{
		ft_posclear(free, 1);
		return (0);
	}
	while (pathtab[i] != 0)
	{
		execve(ft_strjoin(ft_strjoin(pathtab[i], "/", free), cmd[0], free), cmd, env);
		i++;
	}
	return (0);
}

void	ft_parent(char **argv, char **env, int pipe[2] ,t_pos *free)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	dup2(pipe[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe[1]);
	ft_execute(argv, env, 3, free);
}

void	ft_child(char **argv, char **env, int pipe[2] ,t_pos *free)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	dup2(pipe[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pipe[0]);
	ft_execute(argv, env, 2,free);
}

int	main(int argc, char **argv, char **env)
{
	t_pos	*free;
	int	pid;
	int	pipe2[2];

	if (argc != 5)
		return (0);
	free = ft_setpos(0);
	if (free == 0)
		return (0);
	pipe(pipe2);
	pid = fork();
	if (pid == 0)
		ft_child(argv, env, pipe2, free);
	waitpid(pid, 0, 0);
	pid = fork();
	if (pid == 0)
		ft_parent(argv, env, pipe2, free);
	waitpid(pid, 0, 0);


	write(1, "1", 1);
	ft_posclear(free, 1);
}
