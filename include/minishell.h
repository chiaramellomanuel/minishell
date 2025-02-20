/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:43:03 by mchiaram          #+#    #+#             */
/*   Updated: 2025/02/20 16:52:27 by mchiaram         ###   ########.fr       */
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
# include <termios.h>

extern int	g_kill_pid;

void		fill_t_token(t_parse *data, t_token *tok);
void		check_pid(t_token *data, int pid);
int			**handle_pipes(t_token *data, int ncommand);
int			here_doc(t_token *data);
int			get_tmpfd(t_token *data);
void		do_command(t_token *data);
int			*create_pid(int ncommand);
int			num_command(t_token *cmd);
void		parent_process_hd(t_token *data, int pid);
int			*check_heredoc(t_token *cmd, int ncommand);
int			*handle_redir(t_token *data, int *fd, int i);
int			*first_check_pipes(int *fd, int ncommand, int i, int **pipes);
int			execute_builtin(t_token *data, char *builtin, int fd1);
void		free_all(t_parse *data, t_token *tok, t_environ *env, char **input);
void		free_parse(t_parse *data);
void		free_token(t_token *tok);
void		free_environment(t_environ *env, size_t all);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
char		**add_env_var(char **env, char *var);
void		close_pipes_for_child(int **pipes, int i, int ncommand);
void		close_pipes_for_parent(int **pipes, int i, int ncommand);
void		free_process_memory(int **pipes, int **pids);
char		**update_env_var(char **env, char *var_name, char *value);
char		**copy_env(char **old_env);
char		*ft_getenv(char **env, char *val);
char		*prompt_init(t_token *tok);
t_environ	*init_env(char **envp);

#endif