/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:18:05 by audreyer          #+#    #+#             */
/*   Updated: 2022/07/28 23:13:53 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

char	*ft_getpathline(char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0 && (env[i][0] != 'P' || env[i][1] != 'A'
		|| env[i][2] != 'T' || env[i][3] != 'H' || env[i][4] != '='))
		i++;
	if (env[i] == 0)
		return (0);
	return (&env[i][5]);
}

char	**ft_getpath(t_pipex *pipex, char **env)
{
	char	*pathline;
	char	**pathtab;

	pathline = ft_getpathline(env);
	pathtab = ft_split(pathline, ':', pipex->garbage);
	return (pathtab);
}

char	**ft_getcmd(t_pipex *pipex, char *cmd)
{
	if (ft_strlen(cmd) == 0)
		ft_exit(pipex->garbage,
			"arg empty, same as : parse error near `|'\n");
	return (ft_split(cmd, ' ', pipex->garbage));
}

void	ft_executesimple(t_pipex *pipex, char *cmdfile, char **cmd, char *error)
{
	if (!access(cmdfile, F_OK) && cmdfile[0] == '.' && cmdfile[1] == '/')
	{
		if (!access(cmdfile, X_OK))
			execve(cmdfile, cmd, pipex->env);
		else
			error = cmdfile;
	}
	if (error)
		ft_exit(pipex->garbage, ft_strjoin("permission denied: ",
				ft_strjoin(error, "\n", pipex->garbage), pipex->garbage));
	ft_exit(pipex->garbage, ft_strjoin("command not found: ",
			ft_strjoin(cmd[0], "\n", pipex->garbage), pipex->garbage));
}

void	ft_execute(t_pipex *pipex, char *argv, char **env)
{
	char	**pathtab;
	char	**cmd;
	int		i;
	char	*cmdfile;
	char	*error;

	i = 0;
	error = 0;
	pathtab = ft_getpath(pipex, env);
	if (pathtab == 0)
		ft_exit(pipex->garbage, "no path in env\n");
	cmd = ft_getcmd(pipex, argv);
	if (cmd == 0)
		ft_exit(pipex->garbage, "malloc error\n");
	while (pathtab[i] != 0)
	{
		cmdfile = ft_strjoin(ft_strjoin(pathtab[i], "/", pipex->garbage), cmd[0], pipex->garbage);
		if (!access(cmdfile, F_OK))
		{
			if (!access(cmdfile, X_OK))
				execve(cmdfile, cmd, env);
			else
				error = cmdfile;
		}
		i++;
	}
	ft_executesimple(pipex, cmd[0], cmd, error);
}

int	ft1_close(int fd)
{
	int	closed;

	closed = close(fd);
	if (closed == -1)
		write(2, "n1p", 3);
	return (closed);
}


int	ft2_close(int fd)
{
	int	closed;

	closed = close(fd);
	if (closed == -1)
		write(2, "n2p", 3);
	return (closed);
}


int	ft_close(int fd)
{
	int	closed;

	closed = close(fd);
	if (closed == -1)
		write(2, "nop", 3);
	return (closed);
}

int	*ft_child(t_pipex *pipex, int i, int *prevpipe, int *childid)
{
	int	*newpipe;
	newpipe = ft_malloc(sizeof(int) * 2, pipex->garbage);
	pipe(newpipe);
	childid[i] = fork();
	if (childid[i] == 0)
	{
		if (i == 0)
		{
			dup2(pipex->fdin, 0);
			ft_close(newpipe[0]);
			dup2(newpipe[1], 1);
			ft_close(newpipe[1]);
			ft_close(pipex->fdin);
		}
		else if (i == pipex->argc - 4)
		{
			ft_close(newpipe[0]);
			ft_close(newpipe[1]);
			ft_close(prevpipe[1]);
			dup2(prevpipe[0], 0);
			ft_close(prevpipe[0]);
			dup2(pipex->fdout, 1);
			ft_close(pipex->fdout);
		}
		else
		{
			ft_close(prevpipe[1]);
			dup2(prevpipe[0], 0);
			ft_close(prevpipe[0]);
			ft_close(newpipe[0]);
			dup2(newpipe[1], 1);
			ft_close(newpipe[1]);
			ft_close(pipex->fdout);
		}
		ft_execute(pipex, pipex->argv[i + 2], pipex->env);
	}
	else
	{
		if (i == 0)
		{
			ft_close(pipex->fdin);
		}
		else if (i == pipex->argc - 4)
		{
			ft_close(prevpipe[1]);
			ft_close(prevpipe[0]);
			ft_close(pipex->fdout);
			ft_close(newpipe[0]);
			ft_close(newpipe[1]);
		}
		else
		{
			ft_close(prevpipe[1]);
			ft_close(prevpipe[0]);
		}
	}
	return (newpipe);
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
	pipex->env = env;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->fdin = open(argv[1], O_RDONLY, 0777);
	if (pipex->fdin == -1)
		ft_exit(garbage, "fail open");
	pipex->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (pipex->fdout == -1)
	{
		close(pipex->fdin);
		ft_exit(garbage, "fail open");
	}
	return (pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *pipex;
	int	*mypipe;
	int	i;

	i = 0;
	if (argc < 5)
      		return (0);
	pipex = ft_pipexinit(argc, argv, env);
	mypipe = 0;
	while (i < argc - 3)
	{
		mypipe = ft_child(pipex, i, mypipe, pipex->childid);
		i++;
	}
	while (i-- > 0)
		waitpid(pipex->childid[i], 0, 0);
	ft_exit(pipex->garbage, 0);
}
