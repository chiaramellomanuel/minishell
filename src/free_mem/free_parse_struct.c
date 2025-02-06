/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvigano <gvigano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:48:59 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/06 11:49:00 by gvigano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(t_parse *data)
{
	t_parse	*current;

	if (data)
	{
		current = data;
		while (current)
		{
			if (current->value)
			{
				free (current->value);
				current->value = NULL;
			}
			data = data->next;
			free (current);
			current = NULL;
			current = data;
		}
	}
}
