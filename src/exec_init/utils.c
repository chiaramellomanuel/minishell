/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:42:18 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:42:57 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pid(t_token *data, int pid)
{
	if (pid < 0)
	{
		free_token(data);
		perror("Fork Error");
		exit(EXIT_FAILURE);
	}
}

void	handle_pipe(t_token *data, int fd[2])
{
	if (pipe(fd) < 0)
	{
		free_token(data);
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}
