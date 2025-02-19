/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/17 18:51:56 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_token *data, int fd)
{
	int	i;

	if (data->value[1])
	{
		ft_putstr_fd("No arguments accepted for env\n", 2);
		data->env->exit_stat = EXIT_FAILURE;
		return (0);
	}
	i = 0;
	while (data->env->var[i])
	{
		if (ft_strchr(data->env->var[i], '='))
		{
			ft_putstr_fd(data->env->var[i++], fd);
			ft_putchar_fd('\n', fd);
		}
		else
			i++;
	}
	data->env->exit_stat = 0;
	return (1);
}
