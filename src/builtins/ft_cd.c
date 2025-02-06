/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:24:22 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/06 15:29:51 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_token *data, char *path)
{
	size_t	i;
	char	*pwd;
	char	*old_pwd;
	char	**new_env;

	new_env = copy_env(data->env->var);
	pwd = ft_getenv(data->env->var, "PWD");
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	free_environment(data->env, 0);
	data->env->var = export_var(new_env, old_pwd);
	i = 0;
	while (new_env[i])
		free (new_env[i++]);
	free (new_env);
	free (pwd);
	free (old_pwd);
	pwd = ft_strjoin("PWD", "=");
	pwd = ft_freejoin(pwd, path);
	new_env = copy_env(data->env->var);
	free_environment(data->env, 0);
	data->env->var = export_var(new_env, pwd);
	i = 0;
	while (new_env[i])
		free (new_env[i++]);
	free (new_env);
	free (pwd);
}

void	ft_cd(t_token *data)
{
	char	*path;

	path = NULL;
	if (!data->value[1] || data->value[1][0] == '~')
		path = ft_getenv(data->env->var, "HOME");
	else if (data->value[1][0] == '-')
	{
		path = ft_getenv(data->env->var, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
	}
	if (!path)
		return ;
	update_pwd(data, path);
	chdir(path);
	free (path);
}
