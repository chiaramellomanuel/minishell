/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:42:18 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/17 19:11:19 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_command(t_token *cmd)
{
	int		ncommand;

	if (!cmd || !cmd->value)
		return (0);
	ncommand = 0;
	while (cmd)
	{
		ncommand++;
		cmd = cmd->next;
	}
	return (ncommand);
}

int	*create_pid(int ncommand)
{
	int		*pids;

	pids = ft_calloc(ncommand, sizeof(int));
	if (!pids)
	{
		perror("pide malloc failed");
		exit(EXIT_FAILURE);
	}
	return (pids);
}

void	check_pid(t_token *data, int pid)
{
	if (pid < 0)
	{
		free_token(data);
		perror("Fork Error");
		exit(EXIT_FAILURE);
	}
}

void	free_process_memory(int **pipes, int *pids)
{
	int		i;

	i = 0;
	if (pipes)
	{
		while (pipes[i])
			free (pipes[i++]);
		free (pipes);
	}
	if (pids)
		free (pids);
}
