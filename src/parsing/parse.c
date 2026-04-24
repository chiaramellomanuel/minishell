/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:12 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/24 10:40:15 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	remove_quotes(t_parse *data)
// {
// 	char	*str;

// 	str = ft_substr(data->value, 1, (ft_strlen(data->value) - 2));
// 	free (data->value);
// 	data->value = ft_strdup("\0");
// 	if (*str)
// 	{
// 		free (data->value);
// 		data->value = ft_strdup(str);
// 	}
// 	free (str);
// }

char	*expand_var(t_token *tok, char *var)
{
	size_t	i;
	char	*var_name;
	char	*var_exp;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	var_name = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
	{
		var_name[i] = var[i];
		i++;
	}
	var_exp = ft_getenv(tok->env->var, var_name);
	free(var_name);
	return (var_exp);
}

int	check_path_access(char *dir, char *value)
{
	char	*path;

	path = ft_strjoin(dir, "/");
	path = ft_freejoin(path, value);
	if (access(path, X_OK) == 0)
	{
		free (path);
		return (1);
	}
	free (path);
	return (0);
}

int	input_parse(char **input, t_parse *data, t_token *tok)
{
	if (!fill_t_parse_values(*(input), data, tok)
		|| !fill_t_parse_types(data, tok))
	{
		free_all(data, NULL, NULL, input);
		return (0);
	}
	fill_t_token(data, tok);
	free_all(data, NULL, NULL, input);
	return (1);
}
