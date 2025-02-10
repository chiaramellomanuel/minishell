/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:46:18 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/10 17:25:57 by menny            ###   ########.fr       */
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
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}
