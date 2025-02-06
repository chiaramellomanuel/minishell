/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:36:25 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_token *data)
{
	int	i;

	i = 0;
	while (data->env->var[i])
	{
		if (ft_strchr(data->env->var[i], '='))
			printf("%s\n", data->env->var[i++]);
		else
			i++;
	}
	data->env->exit_stat = 0;
}
