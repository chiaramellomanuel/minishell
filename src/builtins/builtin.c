/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/17 18:42:55 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_builtins(t_token *data, char *builtin, int fd)
{
	char	**new_env;
	size_t	i;

	data->env->exit_stat = 0;
	if (!ft_strcmp(builtin, "unset") && data->value[1])
	{
		i = 1;
		while (data->value[i])
		{
			new_env = ft_unset(data->env->var, data->value[i++]);
			free_environment(data->env, 0);
			data->env->var = new_env;
		}
	}
	else if (!ft_strcmp(builtin, "export"))
	{
		if (!ft_export(data, fd))
			data->env->exit_stat = 1;
	}
	else
	{
		if (!ft_cd(data))
			data->env->exit_stat = 1;
	}
}

int	execute_builtin(t_token *data, char *builtin, int fd1)
{
	if (ft_strcmp(builtin, "echo") == 0)
		ft_echo(data, fd1);
	else if (ft_strcmp(builtin, "pwd") == 0)
		ft_pwd(data, fd1);
	else if (ft_strcmp(builtin, "env") == 0)
	{
		if (!ft_env(data, fd1))
			return (0);
	}
	else if (ft_strcmp(builtin, "exit") == 0)
		ft_exit(data);
	else if (!ft_strcmp(builtin, "unset")
		|| !ft_strcmp(builtin, "export")
		|| !ft_strcmp(builtin, "cd"))
		env_builtins(data, builtin, fd1);
	return (1);
}
