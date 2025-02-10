/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/10 17:24:41 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_hd(char *limiter, int fd0, int fd1, t_token *data)
{
	char	*line;

	close(fd0);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) < 0
			|| ft_strncmp(line, limiter, ft_strlen(limiter) > 0))
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
	exit(EXIT_SUCCESS);
}

static int	here_doc(t_token *data)
{
	int		pid_r;
	int		fd[2];
	char	*limiter;

	limiter = data->rd->name;
	handle_pipe(data, fd);
	pid_r = fork();
	g_kill_pid = pid_r;
	check_pid(data, pid_r);
	if (pid_r == 0)
		child_process_hd(limiter, fd[0], fd[1], data);
	else
	{
		close(fd[1]);
		wait(NULL);
	}
	return (fd[0]);
}

static void	handle_input_redir(t_token *data, int *tmpin)
{
	if (data->rd && data->rd->type == T_RED_IN)
	{
		*tmpin = open(data->rd->name, O_RDONLY);
		if (*tmpin < 0)
		{
			free_token(data);
			perror("Error opening input file");
			exit(EXIT_FAILURE);
		}
	}
	else if (data->rd && data->rd->type == T_DELIM)
	{
		if (data->rd->name)
			*tmpin = here_doc(data);
		else
		{
			free_token(data);
			perror("Error delimiter here_doc");
			exit(EXIT_FAILURE);
		}
	}
	else
		*tmpin = dup(STDIN_FILENO);
}

static void	handle_output_redir(t_token *data, int *tmpout)
{

	if (data->rd && data->rd->type == T_RED_OUT)
	{
		*tmpout = open(data->rd->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*tmpout < 0)
		{
			free_token(data);
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
	}
	else if (data->rd && data->rd->type == T_RED_APPEN)
	{
		*tmpout = open(data->rd->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*tmpout < 0)
		{
			free_token(data);
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
	}
	else

		*tmpout = dup(STDOUT_FILENO);
}

void	handle_redir(t_token *data)
{
	int		tmpin;
	int		tmpout;

	handle_input_redir(data, &tmpin);
	if (tmpin != STDIN_FILENO)
	{
		dup2(tmpin, STDIN_FILENO);
		close(tmpin);
	}
	handle_output_redir(data, &tmpout);
	if (tmpout != STDIN_FILENO)
	{
		dup2(tmpout, STDOUT_FILENO);
		close(tmpout);
	}
}
