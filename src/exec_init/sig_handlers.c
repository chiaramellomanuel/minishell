/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:46:18 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/23 18:55:09 by menny            ###   ########.fr       */
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
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (g_kill_pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_kill_pid == -2)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}
