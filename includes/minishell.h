/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 14:11:29 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// // ~-~-~-~-~-~-~-~-~    Includes    ~-~-~-~-~-~-~-~-~ // //

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
//
# include <readline/history.h>
# include <readline/readline.h>
# define RD_OUT 0
# define WR_IN 1
# define CMD_NF "command not found"
# define N_FD "so such file of directory"
# define IS_D "Is a directory"

// // ~-~-~-~-~-~-~-~-~ Variables	~-~-~-~-~-~-~-~-~ // //

extern char				**environ;
volatile sig_atomic_t	g_sig;

// // ~-~-~-~-~-~-~-~-~ Structs		~-~-~-~-~-~-~-~-~ // //

typedef struct s_token
{
	int					stream_num;
	int					fd_in;
	int					fd_out;
	char				*in_file;
	char				*out_file;
	char				*hd_file;
	char				**arg;
	int					error;
	int					ori_sdtin;
	char				**copy_env;
}						t_token;

// ~-~-~-~-~-~-~-~-~    Functions   ~-~-~-~-~-~-~-~-~ //

// ---  Main        --- //

char					**ft_init_envvars(void);
int						wh_space(char input);
int						spec_char(char input);
int						return_value(int num, bool set_num);
char					*get_input(void);

// ---  Pipe        --- //

int						start_process(char *input, char ***copy_env);

// ---  Stream        --- //

t_token					*init_stream(t_token *stream, int ori_sdtin, int num_pipes);
char					*stream_input(char *input, int u);

// ---  Signal        --- //

void					handle_cmd_c(int sig);
void					setup_signals(void);

// ---  Environment    --- //

char					**ft_add_envvar(char *arg, char **copy_env);
char					**ft_rm_envvar(char *arg, char **copy_env);
char					**ft_update_envvar(char *arg, char *name,
							char **copy_env);
bool					ft_env_exists(char *arg, char **copy_env);
int						find_envp(char *str, char **copy_env);
int						ft_valid_arg(char *arg, bool *plus);

// --- String arrays --- //

char					**ft_strarrdup(char **sstr);
char					**ft_strarrdup_sort(char **sstr);
int						ft_strarrlen(char **sstr);
char					*ft_str_tolower(char *str);

// ---  Builtin_cmds    --- //
int						ft_exe_cd(t_token *stream, char ***copy_env);
int						ft_exe_echo(t_token *stream);
int						ft_exe_env(t_token *stream, char **copy_env);
int						ft_exe_exit(t_token *stream);
int						ft_exe_export(t_token *stream, char ***copy_env);
int						ft_export_empty(t_token *stream, char ***copy_env);
int						ft_export_plus(char ***copy_env, char **arg);
int						ft_exe_pwd(t_token *stream);
int						ft_exe_unset(t_token *stream, char ***copy_env);

// ---  Commands    --- //

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
bool					ft_slash_syntax(char **arg, t_token *stream,
							char ***copy_env);
bool					ft_isdir(struct stat file_info);
bool					ft_isregfile(struct stat file_info);
bool					ft_init_stat(char *arg, t_token *stream,
							struct stat *file_info);

// ---  Inputhandle --- //

int						input_handle(char *input, t_token *stream_one,
							char **copy_env);
int						redirect_out(char *input, int i, t_token *stream,
							char **copy_env);
int						redirect_in(char *input, int i, t_token *stream);
char					*dollar_handle(char *input, char **copy_env,
							t_token *stream);
int						args_handle(char *input, int i, t_token *stream,
							char **copy_env);
int						skip_until_char(int i, char *input, char cha);
int						add_until_char(int i, char *input, char cha,
							char **dst);
char					*str_quote_less(char *input, int len);
int						heredoc(int *i, char *input, char **copy_env,
							int num_pipes);
int						env_char(char input);
void					mem_fail(t_token *stream);
int						if_heredoc(int i, char *input);
int						found_quote(int i, char **input, char **copy_env,
							t_token *stream);
char					*dollar_found(int i, char *input, char **copy_env,
							t_token *stream);
int						if_redir_empty_file(int i, char *input, char **copy_env,
							t_token *stream);
char					*creat_env_str(int i, int i_temp, char *input);
int						check_syntax(char *input);
int						heredoc_child_process(char *str, char *here_doc,
							char **copy_env);
int						stream_handle(char *input, char ***copy_env,
							t_token *stream);
int						skip_heredoc(int i, char *input);
char					*change_input_noarg(char *input, char *str,
							char *env_arg, int i);
char					*change_input_split(char *input, char *str,
							char **env_arg_split, char *input_temp);
int						set_fd_in(t_token *stream);
int						redir_char(char input);
void					am_rd(char *str_temp);

// ---  Pipe --- //
int						pipe_handle(int num_pipe, int ori_sdtin, char *input,
							char ***copy_env);
t_token					*setup_child(int *fds, char *input, t_token *stream,
							int num_pipes);
void					mother_pipe(int i, char *input, t_token *stream,
							char ***copy_env);
void					end_mother_pipe(int *fds, int pid, t_token *stream);

// ---	Errors			--- //

void					ft_error(char *message, char *name);
void					ft_errmal(char *message);
void					free_strarr(char **sstr);
void					free_stream(t_token *stream);
void					ft_closefdout(t_token *stream);
void					token_err(t_token *stream, int value);

#endif
