#include "include/pipex.h"

int	main(int argc, char **argv)
{
	t_pipex *pipex;
	int	*chi;

	(void)argc;
	(void)argv;
	pipex = malloc(sizeof(pipex));
	if (pipex == 0)
		return (0);
	pipex->argv = argv;
//	chi = malloc(sizeof(int));
	(void)chi;
}
