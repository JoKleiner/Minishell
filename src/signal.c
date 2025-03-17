/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:49:20 by joklein           #+#    #+#             */
/*   Updated: 2025/03/14 10:35:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	change_sig_cmd(void)
// {
// 	struct termios	term;
//     struct termios	term_new;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term_new.c_lflag &= ~ECHOCTL; // Deaktiviert die Anzeige von ^C, ^D usw.
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term_new);
// }

// void	handle_cmd_c(int sig)
// {
// 	(void)sig;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handle_cmd_bs(int sig)
// {
// 	(void)sig;
// }

void	handle_cmd_c(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_cmd_bs(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_cmd_c;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	
	sa_quit.sa_handler = handle_cmd_bs;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
