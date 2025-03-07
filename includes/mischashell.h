/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mischashell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:34:38 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/07 09:28:06 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISCHASHELL_H
# define MISCHASHELL_H

# include "minishell.h"

// ---	Commands	--- //

void		ft_exe_cd(char **arglist);
void		ft_execute_command(t_list *stream_one, char **envp);
void		ft_exe_echo(char **arglist);
void		ft_exe_env(char **arglist);
void		ft_exe_exit(char **arglist);
void		ft_exe_export(char **arglist);
void		ft_exe_pwd(char **arglist);
void		ft_exe_unset(char **arglist);

#endif