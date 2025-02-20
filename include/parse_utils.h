/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:17:58 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/20 11:20:15 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "struct.h"

int		input_parse(char **input, t_parse *data, t_token *tok);
int		fill_t_parse_values(char *input, t_parse *data);
int		fill_t_parse_types(t_parse *data, t_token *tok);
int		check_path_access(char *dir, char *value);
size_t	first_tok_copy(t_parse *data, t_token *tok, t_redir *rd, size_t i);
size_t	get_tok(t_parse *data, t_token *new_tok, t_redir *new_rd, size_t i);
int		check_if_builtin(char *value);
char	*expand_var(t_token *tok, char *var);
void	remove_quotes(t_parse *data);
void	manage_var(t_parse *data, t_token *tok, size_t i);
void	manage_new_rd(t_redir *rd, t_parse *data, t_token *tok);
void	free_redirect(t_redir *rd);

#endif