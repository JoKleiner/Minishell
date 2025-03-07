/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/07 10:16:18 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// // ~-~-~-~-~-~-~-~-~    Includes    ~-~-~-~-~-~-~-~-~ // //

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
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
	int stream_num;	//stream_num
	int fd_in;      // 1 für std_input, 2 für Pipe, 3 für File
	int fd_out;     // 1 für std_out, 2 für Pipe, 3 für File
	char *in_file;  // input File
	char *out_file; // File in das der Comand schreibt/ausgeführt wird.
	char **arg;     // die argumente
	bool add;       	// 1 wenn ">>"
}				t_token;

typedef struct s_data
{
	char	*path;
	char	**try_paths;
}				t_data;

// ~-~-~-~-~-~-~-~-~    Functions   ~-~-~-~-~-~-~-~-~ //

// ---  Main        --- //

t_list			*init_stream(t_list *stream_one);
int				wh_space(char input);
int				wr_symbol(char input);

// ---  Commands    --- //

void			ft_execute_command(t_list *stream_one, char **envp);
void			ft_exe_cd(char **arglist);
void			ft_exe_echo(char **arglist);
void			ft_exe_env(char **arglist);
void			ft_exe_exit(char **arglist);
void			ft_exe_export(char **arglist);
void			ft_exe_pwd(char **arglist);
void			ft_exe_unset(char **arglist);

// ---  Inputhandle --- //

int				input_handle(char *input, t_list *stream_one);
int				redirect_in(char *input, int i, t_list *stream);
int				redirect_out(char *input, int i, t_list *stream);
int				heredoc(int i, char *input, t_list *stream);
char			*dollar_handle(char *input, t_list *stream);
#endif
