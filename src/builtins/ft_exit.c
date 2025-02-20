/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/20 16:55:43 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token *data)
{
	int		exit_nbr;

	exit_nbr = 0;
	if (data->value[1])
		exit_nbr = ft_atoi(data->value[1]);
	free_environment(data->env, 1);
	free_token(data);
	unlink("heredoc_tmp.txt");
	exit(exit_nbr);
}
