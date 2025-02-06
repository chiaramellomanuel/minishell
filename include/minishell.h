/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:03 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/05 19:07:53 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "struct.h"
# include "builtin.h"
# include "parse_utils.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

int			init(t_parse *data, t_token *tok, char **envp);
void		check_pid(t_token *data, int pid);
void		handle_pipe(t_token *data, int fd[2]);
void		do_command(t_token *data);
void		handle_redir(t_token *data);
void		fill_t_token(t_parse *data, t_token *tok);
void		execute_builtin(t_token *data, char *builtin, int fd1);
void		free_all(t_parse *data, t_token *tok, t_environ *env, char **input);
void		free_parse(t_parse *data);
void		free_token(t_token *tok);
void		free_environment(t_environ *env, size_t all);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
char		**add_env_var(char **env, char *var);
char		**update_env_var(char **env, char *var_name, char *value);
char		**copy_env(char **old_env);
char		*ft_getenv(char **env, char *val);
char		*prompt_init(t_token *tok);
t_environ	*init_env(char **envp);

#endif