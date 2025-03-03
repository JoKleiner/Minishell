/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/03 11:04:26 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(void)
// {
// 	int		pi_fds[2];
// 	pid_t	pid;
// 	char	buff[2];
// 	int		fd;

// 	pipe(pi_fds);
// 	pid = fork();
// 	if (pid == 0)   // pid == 0 rechte Seite der Pipe
// 	{
// 		close(pi_fds[WR_IN]);
// 		fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		dup2(fd, 1);
// 		while (read(pi_fds[RD_OUT], buff, 1))
// 		{
// 			write(1, buff, 1);
// 		}
// 		close(pi_fds[RD_OUT]);
// 	}
// 	else
// 	{
// 		close(pi_fds[RD_OUT]);
// 		write(pi_fds[WR_IN], "servus\n", 7);
// 		close(pi_fds[WR_IN]);
// 	}
// 	waitpid(pid, 0, 0);
// 	return (0);
// }

// void	execute_command(char **args)
// {
// 	ft_printf("%s\n", args[0]);
// 	ft_printf("%s\n", args[1]);
// 	ft_printf("%s\n", args[2]);
// 	char **args={"a", NULL};
// 	execve("/bin/cat", args, NULL);
// }

t_list	*init_stream(t_token *stream_info)
{
	t_list	*stream;

	stream_info = (t_token *)malloc(sizeof(t_token));
	if (!stream_info)
		return (NULL);
	stream = ft_lstnew(stream_info);
	TOKEN->input = 1;
	TOKEN->output = 1;
	TOKEN->in_file = NULL;
	TOKEN->out_file = NULL;
	TOKEN->cmd = NULL;
	TOKEN->arg = NULL;
	TOKEN->add = 0;
	return (stream);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*stream;
	t_token	*stream_info;

	// char	**args;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return(free(input), 0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_info = NULL;
		stream = init_stream(stream_info);
		if (stream == NULL)
			return (0);
		// args =
		input_handle(input, stream);
		// if (strcmp(args[0], "exit") == 0)
		// {
		// 	free(input);
		// 	free(args);
		// 	break ;
		// }
		// execute_command(args);
		// free(input);
		// free(args);
	}
	return (0);
}
