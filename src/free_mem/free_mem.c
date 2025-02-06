/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:15:56 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/05 10:57:15 by menny            ###   ########.fr       */
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
