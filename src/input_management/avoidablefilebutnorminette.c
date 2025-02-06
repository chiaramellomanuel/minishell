/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avoidablefilebutnorminette.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:35:06 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 13:35:07 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_var(t_parse *data, t_token *tok, size_t i)
{
	char	*str;
	char	*var_val;

	str = ft_substr(data->value, i, ft_strlen(data->value));
	var_val = expand_var(tok, str);
	free (str);
	str = ft_substr(data->value, 0, (i - 1));
	if (var_val)
	{
		str = ft_freejoin(str, var_val);
		free (var_val);
	}
	while (data->value[i] && (ft_isalnum(data->value[i])
			|| data->value[i] == '_'))
		i++;
	var_val = ft_substr(data->value, i, ft_strlen(data->value));
	str = ft_freejoin(str, var_val);
	free (var_val);
	free (data->value);
	data->value = ft_strdup(str);
	free (str);
}
