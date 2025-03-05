/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/04 15:45:56 by joklein          ###   ########.fr       */
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

t_list	*init_stream(t_list *stream_one)
{
	t_list	*stream;
	t_token	*stream_info;

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
	ft_lstadd_back(&stream_one, stream);
	return (stream);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*stream_one;
	t_list	*stream;
	int		i;
	int		u;

	(void)argc;
	(void)argv;
	(void)envp;
	stream_one = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (free(input), write(1, "exit", 4), 0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_one = init_stream(stream_one);
		if (stream_one == NULL)
			return (free(input), 0);
		i = input_handle(input, stream_one);
		if (i == 1)
			return (1);
		stream = stream_one;
		u = 1;
		while (stream)
		{
			if (TOKEN->arg)
			{
				ft_printf("\n");
				i = 0;
				ft_printf("Stream: %d\ninput: %d\noutput:%d\ninfile:%s\noutfile: %s\ncmd: %s\nadd: %d\n", u,
					TOKEN->input, TOKEN->output, TOKEN->in_file,TOKEN->out_file, TOKEN->cmd, TOKEN->add);
				while (TOKEN->arg[i])
				{
					ft_printf("arg[%d]:%s\n", i, TOKEN->arg[i]);
					i++;
				}
				ft_printf("\n");
				
			}
			stream = stream->next;
			u++;
		}
		// execute_command(stream_one);
		free(input);
	}
	return (0);
}
