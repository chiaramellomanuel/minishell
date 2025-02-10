/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/10 15:47:07 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_token *data, int fd)
{
	int	i;

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
}
