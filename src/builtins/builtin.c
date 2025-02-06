/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 14:24:17 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_builtins(t_token *data, char *builtin)
{
	char	**new_env;
	size_t	i;

	if (!ft_strncmp(builtin, "unset", ft_strlen(builtin)) && data->value[1])
	{
		i = 1;
		while (data->value[i])
		{
			new_env = ft_unset(data->env->var, data->value[i++]);
			free_environment(data->env, 0);
			data->env->var = new_env;
		}
	}
	else if (!ft_strncmp(builtin, "export", ft_strlen(builtin)))
	{
		if (ft_export(data))
			data->env->exit_stat = 0;
		else
			data->env->exit_stat = 1;
	}
	else
		ft_cd(data);
}

void	execute_builtin(t_token *data, char *builtin, int fd1)
{
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		ft_echo(data, fd1);
	else if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		ft_pwd(data, fd1);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		ft_env(data);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
		ft_exit(data);
	else if (!ft_strncmp(builtin, "unset", ft_strlen(builtin))
		|| !ft_strncmp(builtin, "export", ft_strlen(builtin))
		|| !ft_strncmp(builtin, "cd", ft_strlen(builtin)))
		env_builtins(data, builtin);
}
