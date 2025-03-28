/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_ms.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:27:59 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 15:49:26 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_MS_H
# define OUTPUT_MS_H

# include "minishell.h"

typedef struct s_token	t_token;

// -----  Environment  ----- //
char					**ft_add_envvar(char *arg, char **copy_env);
char					**ft_rm_envvar(char *arg, char **copy_env);
char					**ft_update_envvar(char *arg, char *name,
							char **copy_env);
bool					ft_env_exists(char *arg, char **copy_env);
int						find_envp(char *str, char **copy_env);
int						ft_valid_arg(char *arg, bool *plus);
int						env_char(char input);

// -----  String arrays  ----- //
char					**ft_strarrdup(char **sstr);
char					**ft_strarrdup_sort(char **sstr);
int						ft_strarrlen(char **sstr);
char					*ft_str_tolower(char *str);

// -----  Builtin_cmds  ----- //
int						ft_exe_cd(t_token *stream, char ***copy_env);
int						ft_exe_echo(t_token *stream);
int						ft_exe_env(t_token *stream, char **copy_env);
int						ft_exe_exit(t_token *stream);
int						ft_exe_export(t_token *stream, char ***copy_env);
int						ft_export_empty(t_token *stream, char ***copy_env);
int						ft_export_plus(char ***copy_env, char **arg);
int						ft_exe_pwd(t_token *stream);
int						ft_exe_unset(t_token *stream, char ***copy_env);

// -----  Commands  ----- //
void					ft_execute_command(t_token *stream, char ***copy_env);
int						ft_execute_cmd_fork(char *path, t_token *stream,
							char ***copy_env);
bool					ft_builtin_cmd(char *name, t_token *stream,
							char ***copy_env);
bool					ft_cmd_in_path(t_token *stream, char ***copy_env);
bool					ft_non_accessible(t_token *stream);
bool					ft_is_executable(char *arg, t_token *stream,
							char ***copy_env);
bool					ft_dot_syntax(char **arg, t_token *stream,
							char ***copy_env);
bool					ft_isdir(struct stat file_info);
bool					ft_isregfile(struct stat file_info);
bool					ft_init_stat(char *arg, t_token *stream,
							struct stat *file_info);

#endif
