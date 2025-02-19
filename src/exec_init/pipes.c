#include "minishell.h"

int	*first_check_pipes(int ncommand, int i, int **pipes)
{
	int		*fd;

	fd = ft_calloc(2, sizeof(int));
	fd[0] = STDIN_FILENO;
	if (i > 0)
		fd[0] = pipes[i - 1][0];
	fd[1] = STDOUT_FILENO;
	if (i < ncommand - 1)
		fd[1] = pipes[i][1];
	return (fd);
}

void	close_pipes_for_parent(int **pipes, int i, int ncommand)
{
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < (ncommand - 1))
		close(pipes[i][1]);
}

void	close_pipes_for_child(int **pipes, int i, int ncommand)
{
	int		j;

	j = 0;
	while (j < (ncommand - 1))
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

int	**handle_pipes(t_token *data, int ncommand)
{
	int		i;
	int		**pipes;

	if (ncommand <= 1)
		return (NULL);
	pipes = ft_calloc((ncommand), sizeof(int *));
	if (!pipes)
	{
		free_token(data);
		perror("Pipe malloc failed");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < (ncommand - 1))
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes || pipe(pipes[i]) == -1)
		{
			free_token(data);
			perror("Pipe error");
			exit (EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}
