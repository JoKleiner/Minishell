/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/17 12:16:48 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// // ~-~-~-~-~-~-~-~-~    Includes    ~-~-~-~-~-~-~-~-~ // //

# include "../libft/libft.h"
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
# define TOKEN ((t_token *)stream->cont)

// // ~-~-~-~-~-~-~-~-~ Variables	~-~-~-~-~-~-~-~-~ // //

extern char		**environ;
volatile int	g_sig;

// // ~-~-~-~-~-~-~-~-~ Structs		~-~-~-~-~-~-~-~-~ // //

typedef struct s_token
{
	int stream_num; // stream_num
	int fd_in;      // 0 für std_input, 2 für Pipe, 3 für File, 4 for heredoc
	int fd_out;     // fd output, 1 für std_output
	char *in_file;  // input File
	char *out_file; // File in das der Comand schreibt/ausgeführt wird.
	char *hd_file;  // heredoc file
	char **arg;     // die argumente
}				t_token;

// ~-~-~-~-~-~-~-~-~    Functions   ~-~-~-~-~-~-~-~-~ //

// ---  Main        --- //

t_list			*init_stream(t_list *stream_one);
int				wh_space(char input);
int				spec_char(char input);
int				spec_char_wo_dol(char input);

// ---  Signal        --- //
void            handle_cmd_c(int sig);
void            setup_signals(void);

// ---  Environment    --- //

char			**ft_add_envvar(char *arg, char **copy_env);
char			**ft_rm_envvar(char *arg, char **copy_env);
char			**ft_update_envvar(char *arg, char *name, char **copy_env);
bool			ft_env_exists(char *arg, char **copy_env);
int				find_envp(char *str, char **copy_env);

// --- String arrays --- //

char			**ft_strarrdup(char **sstr);
char			**ft_strarrdup_sort(char **sstr);
int				ft_strarrlen(char **sstr);

// ---  Commands    --- //

void			ft_exe_cd(t_list *stream, char ***copy_env);
void			ft_execute_command(t_list *stream, char ***copy_env);
void			ft_exe_echo(t_list *stream);
void			ft_exe_env(t_list *stream, char **copy_env);
void			ft_exe_exit(t_list *stream);
void			ft_exe_export(t_list *stream, char ***copy_env);
void			ft_exe_pwd(t_list *stream);
void			ft_exe_unset(t_list *stream, char ***copy_env);

// ---  Inputhandle --- //

int				input_handle(char *input, t_list *stream_one, char **copy_env);
int				redirect_out(char *input, int i, t_list *stream);
int				redirect_in(char *input, int i, t_list *stream,
					char **copy_env);
char			*dollar_handle(char *input, char **copy_env);
int				creat_args(char *input, int i, t_list *stream);
int				skip_until_char(int i, char *input, char cha);
char			*str_quote_less(char *input, int len);
int				heredoc(int i, char *input, t_list *stream, char **copy_env);
int				env_char(char input);
;
int				if_heredoc(int i, char *input);
int				found_quote(int i, char *input, char **copy_env);
char			*dollar_found(int i, char *input, char **copy_env);
int				if_redir_empty_file(int i, char *input, char **copy_env);
char			*creat_str(int i, int i_temp, char *input);

// ---	Errors			--- //

void			ft_error_cmd(char *message, char *name);
void			free_strarr(char **sstr);
void			free_stream(t_list *stream);

#endif
