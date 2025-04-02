/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:43 by joklein           #+#    #+#             */
/*   Updated: 2025/04/02 15:24:50 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// // ~-~-~-~-~-~-~-~-~    Includes    ~-~-~-~-~-~-~-~-~ // //

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

// -----  Header  ----- //
# include "../libft/libft.h"
# include "input_ms.h"
# include "output_ms.h"

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

// -----  Main  ----- //
char					**ft_init_envvars(void);
int						wh_space(char input);
int						spec_char(char input);
int						return_value(int num, bool set_num);
char					*get_input(void);
int						check_syntax(char *input);

// -----  Stream  ----- //
char					*stream_input(char *input, int u);
t_token					*init_stream(t_token *stream, int ori_sdtin,
							int num_pipes);

// -----  Signal  ----- //
void					handle_cmd_c(int sig);
void					setup_signals(void);
// void					setup_signal_child(void);
void					new_signal(void);
void					sig_default(int sig);

// -----  Error  ----- //
void					ft_error(char *message, char *name);
void					ft_errmal(char *message);
void					free_strarr(char **sstr);
void					free_sm(t_token *stream);
void					ft_closefdout(t_token *stream);
void					token_err(t_token *stream, int value);
void					mem_fail(t_token *stream);

#endif
