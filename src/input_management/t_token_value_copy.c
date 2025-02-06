/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_value_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:22:57 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/06 13:43:51 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(t_token *tok, char *value)
{
	char	*path_env;
	char	**dir;
	int		i;

	path_env = ft_getenv(tok->env->var, "PATH");
	if (!path_env)
		return (0);
	dir = ft_split(path_env, ':');
	path_env = ft_freelcopy(&path_env, value, ft_strlen(value));
	i = -1;
	while (dir[++i])
	{
		if (check_path_access(dir[i], value))
		{
			free(path_env);
			path_env = ft_strjoin(dir[i], "/");
			path_env = ft_freejoin(path_env, value);
			break ;
		}
	}
	i = 0;
	while (dir[i])
		free (dir[i++]);
	free (dir);
	return (path_env);
}

static void	*expand_exit_stat(t_parse *data, t_token *tok)
{
	int		i;
	char	*str;
	char	*temp;
	char	*temp2;

	str = ft_strdup(data->value);
	i = -1;
	while (str[++i] && data->type != T_QUOTE)
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			temp = ft_substr(str, 0, i);
			temp2 = ft_itoa(tok->env->exit_stat);
			temp = ft_freejoin(temp, temp2);
			free (temp2);
			temp2 = ft_substr(str, (i + 2), ft_strlen(str));
			temp = ft_freejoin(temp, temp2);
			free (temp2);
			free (str);
			str = ft_strdup(temp);
			free (temp);
			i = -1;
		}
	}
	return (str);
}

size_t	get_tok(t_parse *data, t_token *new_tok, t_redir *new_rd, size_t i)
{
	if (data && (data->type >= T_GENERAL && data->type <= T_COMMAND))
	{
		if (data->type >= T_QUOTE && data->type <= T_VAR)
		{
			if (data->type == T_QUOTE || data->type == T_DQUOTE)
				remove_quotes(data);
			if (data->value)
				new_tok->value[i++] = expand_exit_stat(data, new_tok);
		}
		else if (i == 0 && data->type != T_BUILTIN)
			new_tok->value[i++] = find_path(new_tok, data->value);
		else
			new_tok->value[i++] = ft_strdup(data->value);
	}
	else if (data && (data->type >= T_RED_IN && data->type <= T_DELIM))
	{
		new_rd->type = data->type;
		new_rd->name = ft_strdup(data->next->value);
	}
	return (i);
}

size_t	first_tok_copy(t_parse *data, t_token *tok, t_redir *rd, size_t i)
{
	if (data && (data->type >= T_GENERAL && data->type <= T_COMMAND))
	{
		if (data->type >= T_QUOTE && data->type <= T_VAR)
		{
			if (data->type == T_QUOTE || data->type == T_DQUOTE)
				remove_quotes(data);
			if (data->value)
				tok->value[i++] = expand_exit_stat(data, tok);
		}
		else if (i == 0 && data->type != T_BUILTIN)
			tok->value[i++] = find_path(tok, data->value);
		else
			tok->value[i++] = ft_strdup(data->value);
	}
	else if (data && (data->type >= T_RED_IN && data->type <= T_DELIM))
	{
		rd->type = data->type;
		rd->name = ft_strdup(data->next->value);
	}
	return (i);
}
