/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:15:56 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/23 17:47:16 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_parse *data, t_token *tok, t_environ *env, char **input)
{
	if (data)
		free_parse(data);
	if (tok)
		free_token(tok);
	if (env)
		free_environment(env, 1);
	if (*(input))
	{
		free (*(input));
		*(input) = NULL;
	}
}

void	free_process_memory(t_token *data, t_environ *env, t_free *fvar)
{
	int		i;

	i = 0;
	if (fvar->pipes)
	{
		while (fvar->pipes[i])
			free (fvar->pipes[i++]);
		free (fvar->pipes);
	}
	if (*(fvar->pids))
	{
		free (*(fvar->pids));
		fvar->pids = NULL;
	}
	if (fvar)
	{
		free (fvar);
		fvar = NULL;
	}
	if (env)
		free_environment(env, 1);
	if (data)
		free_token(data);
}
