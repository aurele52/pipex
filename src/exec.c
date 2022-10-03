/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:21:07 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/03 18:21:28 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	cmd = ft_split(argv, ' ', pipex->garbage);
	if (cmd == 0 || pathtab == 0)
		ft_exit(pipex->garbage, "malloc error\n");
	while (pathtab[i] != 0)
	{
		cmdfile = ft_strjoin(ft_strjoin(pathtab[i++],
					"/", pipex->garbage), cmd[0], pipex->garbage);
		if (!access(cmdfile, F_OK))
		{
			if (!access(cmdfile, X_OK))
				execve(cmdfile, cmd, env);
			else
				error = cmdfile;
		}
	}
	ft_executesimple(pipex, cmd[0], cmd, error);
}
