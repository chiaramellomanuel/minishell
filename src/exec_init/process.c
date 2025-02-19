#include "minishell.h"

static void	execute_bin_bash(t_token *data)
{
	char	*bash_args[4];

	bash_args[0] = "bin/bash";
	bash_args[1] = data->value[0];
	bash_args[2] = NULL;
	if ((!ft_strcmp(data->value[0], "+")
			|| !ft_strcmp(data->value[0], "-"))
		|| execve("/bin/bash", bash_args, data->env->var) == -1)
	{
		ft_putstr_fd(data->value[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_token(data);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static void	child_process(t_token *data, int *fd)
{
	fd = handle_redir(data, fd);
	if (check_if_builtin(data->value[0]))
	{
		if (!execute_builtin(data, data->value[0], fd[1]))
		{
			free_token(data);
			exit(EXIT_FAILURE);
		}
		free_token(data);
		exit(0);
	}
	if (fd[0] != STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (data->value[0]
		&& execve(data->value[0], data->value, data->env->var) == -1)
		execute_bin_bash(data);
	exit(EXIT_SUCCESS);
}

static void	parent_process(t_token *data, int *pid, int ncommand)
{
	int	status;
	int	i;

	i = 0;
	while (i < ncommand)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
			data->env->exit_stat = WTERMSIG(status);
		else
			data->env->exit_stat = WEXITSTATUS(status);
		i++;
	}
	if (data->env->exit_stat == 3)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

static void	handle_process(t_token *cmd, int **pipes, int *pids, int ncommand)
{
	int		i;
	int		*fd;

	i = 0;
	while (i < ncommand)
	{
		fd = first_check_pipes(ncommand, i, pipes);
		pids[i] = fork();
		check_pid(cmd, pids[i]);
		if (pids[i] == 0)
		{
			close_pipes_for_child(pipes, i, ncommand);
			child_process(cmd, fd);
		}
		close_pipes_for_parent(pipes, i, ncommand);
		cmd = cmd->next;
		i++;
		free (fd);
	}
}

void	do_command(t_token *data)
{
	int			**pipes;
	int			ncommand;
	t_token		*cmd;
	int			*pids;

	pipes = NULL;
	pids = NULL;
	cmd = data;
	data->env->exit_stat = 0;
	ncommand = num_command(cmd);
	if (ncommand == 0 && !data->rd)
		return ;
	if (ncommand == 1 && check_if_builtin(data->value[0]))
	{
		execute_builtin(data, data->value[0], 1);
		return ;
	}
	pipes = handle_pipes(data, ncommand);
	cmd = data;
	pids = create_pid(ncommand);
	handle_process(cmd, pipes, pids, ncommand);
	parent_process(data, pids, ncommand);
	free_process_memory(pipes, pids);
}
