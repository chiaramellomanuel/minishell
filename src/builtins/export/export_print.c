/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:39:07 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:39:37 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		write(1, &var[i++], 1);
	if (var[i] == '=')
	{
		write (1, &var[i++], 1);
		write(1, "\"", 1);
		while (var[i])
			write (1, &var[i++], 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	print_export_env(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		i++;
		if (ft_strncmp(env[i - 1], env[i], ft_strlen(env[i])) > 0)
		{
			temp = env[i - 1];
			env[i - 1] = env[i];
			env[i] = temp;
			i = 0;
		}
	}
	i = 0;
	while (env[i])
	{
		ft_printf("\033[38;5;214mexport\033[0m ");
		print_var(env[i++]);
	}
}
