/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:25:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/05 10:25:37 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ~-~-~-~-~-~-~-~-~	Includes	~-~-~-~-~-~-~-~-~ //

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
//
# include <readline/history.h>
# include <readline/readline.h>

# define RD_OUT 0
# define WR_IN 1
# define TOKEN ((t_token *)stream->cont)

// // ~-~-~-~-~-~-~-~-~	Structs 	~-~-~-~-~-~-~-~-~ //

//
typedef struct s_token
{
	int input;      // 1 für std_input, 2 für Pipe, 3 für File
	int output;     // 1 für std_out, 2 für Pipe, 3 für File
	char *in_file;  // input File
	char *out_file; // File in das der Comand schreibt/ausgeführt wird.
	char *cmd;      // cat, echo, grep, ...?
	char **arg;     // die argumente
	int add;       
		// 1 wenn ">>": Erweiterungsbefehl,wenn in file geschrieben wird.
}		t_token;

// ~-~-~-~-~-~-~-~-~	Functions	~-~-~-~-~-~-~-~-~ //

char	**input_handle(char *input, t_list *stream);
int		wh_space(char input);
int		wr_symbol(char input);
t_list	*init_stream(t_list *stream_one);
int		redirect_out(char *input, int i, t_list *stream);
int		redirect_in(char *input, int i, t_list *stream);
void	ft_execute_command(t_list *stream_one, char **envp);

#endif
