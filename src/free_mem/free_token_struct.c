/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:48:40 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:48:41 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirect(t_redir *rd)
{
	free(rd->name);
	free(rd);
	rd = NULL;
}

static void	free_values(char **value)
{
	size_t	i;

	i = 0;
	while (value[i])
		free(value[i++]);
	free (value);
	value = NULL;
}

void	free_token(t_token *tok)
{
	t_token	*current;

	current = tok;
	while (current)
	{
		if (current->value)
			free_values(current->value);
		if (current->rd)
			free_redirect(current->rd);
		tok = tok->next;
		free (current);
		current = NULL;
		current = tok;
	}
}
