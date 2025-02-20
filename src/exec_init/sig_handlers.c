/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:46:18 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/20 14:44:47 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_kill_pid = 0;

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		if (g_kill_pid > 0)
		{
			kill(g_kill_pid, SIGKILL);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (g_kill_pid == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_kill_pid == -2)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}
