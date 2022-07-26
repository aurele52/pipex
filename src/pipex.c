/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:18:05 by audreyer          #+#    #+#             */
/*   Updated: 2022/07/26 16:28:54 by audreyer         ###   ########.fr       */
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

char	**ft_getpath(char **env)
{
	char	*pathline;
	char	**pathtab;

	pathline = ft_getpathline(env);
	pathtab = ft_split(pathline, ':', 0);
	return (pathtab);
}

char	**ft_getcmd(char *cmd)
{
	return (ft_split(cmd, ' ', 0));
}

int	ft_execute(char *argv, char **env)
{
	char	**pathtab;
	char	**cmd;
	int	i;
	
	i = 0;
	pathtab = ft_getpath(env);
	cmd = ft_getcmd(argv);
	if (cmd == 0|| pathtab == 0)
		return (0);
	while (pathtab[i] != 0)
	{
		execve(ft_strjoin(ft_strjoin(pathtab[i], "/", 0), cmd[0], 0), cmd, env);
		i++;
	}
	return (0);
}

int	*ft_child(t_pipex *pipex, int i, int *prevpipe, int *childid)
{
	int	*newpipe;
	newpipe = malloc(sizeof(int) * 2);
	if (i != pipex->argc - 2)
		pipe(newpipe);
	childid[i] = fork();
	if (childid[i] == 0)
	{
		if (i == 0)
		{
			dup2(pipex->fdin, 0);
			close(newpipe[0]);
			dup2(newpipe[1], 1);
			close(newpipe[1]);
		}
		else if (i == pipex->argc - 4)
		{

			close(prevpipe[1]);
			dup2(prevpipe[0], 0);
			close(prevpipe[0]);
			dup2(pipex->fdout, 1);
		}
		else
		{
			close(prevpipe[1]);
			dup2(prevpipe[0], 0);
			close(prevpipe[0]);
			close(newpipe[0]);
			dup2(newpipe[1], 1);
			close(newpipe[1]);
		}
		dprintf(2, "%s = %i \n", pipex->argv[i+2],getpid());
		ft_execute(pipex->argv[i + 2], pipex->env);
	}
	else
	{
		if (i == 0)
			close(pipex->fdin);
		else
		{
			close(prevpipe[1]);
			close(prevpipe[0]);
			if (i == pipex->argc - 4)
				close(pipex->fdout);
		}


	}
//	int	fds;
//
//	fds = 0;
//	while (fds != i)
//		printf("%i = %i\n", i, childid[fds++]);
//	dprintf(2, "main = %i \n",getpid());
	return (newpipe);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *pipex;
	int	*mypipe;
	int	i;
	int	*childid;

	i = 0;
	if (argc < 4)
      		return (0);
	pipex = malloc(sizeof(*pipex));
	if (pipex == 0)
	      	return (0);
	pipex->env = env;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->fdin = open(argv[1], O_RDONLY, 0777);
	pipex->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
	if (pipex->fdin == 0 || pipex->fdout == 0)
		ft_exit(0, 0);
	childid = malloc(sizeof(int) * (argc - 3));
	if (childid == 0)
		ft_exit(0, 0);
//	dprintf(2, "main = %i \n",getpid());
	while (i < argc - 3)
	{
		mypipe = ft_child(pipex, i, mypipe, childid);
		i++;
	}
//	dprintf(2, "main = %i \n",getpid());
//	int	fds;
//
//	fds = 0;
//	while (fds != i)
//		printf("%i = %i\n", i, childid[fds++]);
	while (i-- < 0)
		waitpid(-1, 0, 0);
	ft_exit(0, "OK");
}