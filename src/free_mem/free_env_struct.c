/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:48:16 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:48:17 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environment(t_environ *env, size_t all)
{
	size_t	i;

	i = 0;
	while (env->var[i])
	{
		free(env->var[i]);
		env->var[i] = NULL;
		i++;
	}
	free (env->var);
	env->var = NULL;
	if (all)
	{
		free (env);
		env = NULL;
	}
}
