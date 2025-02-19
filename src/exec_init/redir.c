/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/19 20:20:58 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_hd(int fd0, int fd1, t_token *data)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(data->rd->name, "\n");
	close(fd0);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(line, limiter))
			write(fd1, line, ft_strlen(line));
		else
		{
			free (line);
			break ;
		}
		free (line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd1);
	free_token(data);
	free (limiter);
	exit(EXIT_SUCCESS);
}

static int	here_doc(t_token *data)
{
	int		pid_r;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
	{
		free_token(data);
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
	pid_r = fork();
	g_kill_pid = pid_r;
	check_pid(data, pid_r);
	if (pid_r == 0)
		child_process_hd(fd[0], fd[1], data);
	else
	{
		close(fd[1]);
		waitpid(pid_r, &status, 0);
		if (WIFSIGNALED(status))
			data->env->exit_stat = WTERMSIG(status);
		else
			data->env->exit_stat = WEXITSTATUS(status);
	}
	return (fd[0]);
}

static int	handle_input_redir(t_token *data, t_redir *rd, int tmpin)
{
	if (rd && rd->type == T_RED_IN)
	{
		tmpin = open(rd->name, O_RDONLY);
		if (tmpin < 0)
		{
			free_token(data);
			perror("Error opening input file");
			exit(EXIT_FAILURE);
		}
	}
	else if (rd && rd->type == T_DELIM)
	{
		if (rd->name)
			tmpin = here_doc(data);
		else
		{
			free_token(data);
			perror("Error delimiter here_doc");
			exit(EXIT_FAILURE);
		}
	}
	return (tmpin);
}

static int	handle_output_redir(t_token *data, t_redir *rd, int tmpout)
{
	if (rd && rd->type == T_RED_OUT)
	{
		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmpout < 0)
		{
			free_token(data);
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
	}
	else if (rd && rd->type == T_RED_APPEN)
	{
		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (tmpout < 0)
		{
			free_token(data);
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
	}
	return (tmpout);
}

int	*handle_redir(t_token *data, int *fd)
{
	t_redir	*current;
	size_t	i;

	i = 0;
	current = data->rd;
	while (i < data->nredir)
	{
		fd[0] = handle_input_redir(data, current, fd[0]);
		fd[1] = handle_output_redir(data, current, fd[1]);
		if (data->env->exit_stat == SIGKILL)
			exit(data->env->exit_stat);
		current = current->next;
		i++;
	}
	return (fd);
}
