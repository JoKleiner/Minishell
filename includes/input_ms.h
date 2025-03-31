/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ms.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:28:02 by joklein           #+#    #+#             */
/*   Updated: 2025/03/31 16:50:11 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MS_H
# define INPUT_MS_H

# include "minishell.h"

typedef struct s_token	t_token;

// -----  Inputhandle  ----- //
int						input_handle(char *input, t_token *stream_one,
							char **copy_env);
char					*str_quote_less(char *input, int len);
int						stream_handle(char *input, char ***copy_env,
							t_token *stream);
int						start_process(char *input, char ***copy_env);

// -----  Redirect  ----- //
int						redirect_out(char *input, int i, t_token *stream,
							char **copy_env);
int						redirect_in(char *input, int i, t_token *stream);
int						set_fd_in(t_token *stream);
int						redir_char(char input);
void					am_rd(char *str_temp);

// -----  Dollar  ----- //
char					*dollar_handle(char *input, char **copy_env,
							t_token *stream);
int						skip_until_char(int i, char *input, char cha);
int						add_until_char(int i, char *input, char cha,
							char **dst);
int						found_quote(int i, char **input, char **copy_env,
							t_token *stream);
char					*dollar_found(int i, char *input, char **copy_env,
							t_token *stream);
char					*creat_env_str(int i, int i_temp, char *input);
int						skip_heredoc(int i, char *input);
char					*change_input_noarg(char *input, char *str,
							char *env_arg, int i);
int						if_redir_empty_file(int i, char *input, char **copy_env,
							t_token *stream);

// -----  Arguments  ----- //
int						args_handle(char *input, int i, t_token *stream,
							char **copy_env);
int						count_arg_len2(char *input, int i, int *q_count);

// -----  Heredoc  ----- //
int						heredoc(int *i, char *input, char **copy_env,
							int num_pipes);
int						heredoc_child_process(char *str, char *here_doc,
							char **copy_env);
int						if_heredoc(int i, char *input);

// -----  Pipe  ----- //
int						pipe_handle(int num_pipe, int ori_sdtin, char *input,
							char ***copy_env);
t_token					*setup_child(int *fds, char *input, t_token *stream,
							int num_pipes);
void					mother_pipe(int i, char *input, t_token *stream,
							char ***copy_env);
void					end_mother_pipe(int *fds, int pid, t_token *stream,
							char **copy_env);

#endif
