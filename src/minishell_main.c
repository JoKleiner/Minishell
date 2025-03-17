/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/15 17:35:34 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

int	spec_char(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '$')
		return (1);
	return (0);
}

int	spec_char_wo_dol(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|')
		return (1);
	return (0);
}

t_list	*init_stream(t_list *stream_one)
{
	t_list	*stream;
	t_token	*stream_info;
	int		i;

	stream_info = (t_token *)malloc(sizeof(t_token));
	if (!stream_info)
		return (NULL);
	stream = ft_lstnew(stream_info);
	if (!stream)
		return (free(stream_info), (NULL));
	ft_lstadd_back(&stream_one, stream);
	i = 0;
	while (stream_one->next)
	{
		i++;
		stream_one = stream_one->next;
	}
	TOKEN->stream_num = i;
	TOKEN->fd_in = STDIN_FILENO;
	TOKEN->fd_out = STDOUT_FILENO;
	TOKEN->in_file = NULL;
	TOKEN->out_file = NULL;
	TOKEN->arg = NULL;
	TOKEN->hd_file = NULL;
	return (stream);
}

int	main(void)
{
	char	**copy_env;
	char	*input;
	t_list	*stream_one;
	t_list	*stream;
	int		i;

	copy_env = ft_strarrdup(environ);
	if(!copy_env)
		return(ft_error_cmd("malloc failed!", "minishell"), 1);
	while (1)
	{
		stream_one = NULL;
		input = readline("\033[0;34mminishell> \033[0m");
		if (!input)
			return (write(1, "error\n", 6), 1);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_one = init_stream(stream_one);
		if (stream_one == NULL)
			return (free(input), write(1, "error\n", 6), 1);
		if (input_handle(input, stream_one, copy_env))
			return (free_stream(stream_one), 1);
		stream = stream_one;
		while (stream)
		{
			if (TOKEN->arg)
			{
				ft_printf("\n");
				i = 0;
				ft_printf("stream_num: %d\nfd_in:%d\nfd_out:%d\ninfile:%s\noutfile: %s\nhd_file: %s\n",
					TOKEN->stream_num, TOKEN->fd_in, TOKEN->fd_out,
					TOKEN->in_file, TOKEN->out_file, TOKEN->hd_file);
				if (TOKEN->arg[0])
					while (TOKEN->arg[i])
					{
						ft_printf("arg[%d]:%s\n", i, TOKEN->arg[i]);
						i++;
					}
				ft_printf("\n");
			}
			stream = stream->next;
		}
		ft_execute_command(stream_one, &copy_env);
	}
	free_stream(stream_one);
	free_strarr(copy_env);
	rl_clear_history();
	return (0);
}

// Nicht löschen. für pipe verständnis
// int	main(void)

// {
// 	int fds[2];
// 	int pid;
// 	char buff[2];
// 	int fd;

// 	pipe(fds);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fds[1]);
// 		fd = open("baum", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		dup2(fd, 1);
// 		while (read(fds[0], buff, 1))
// 		{
// 			write(1, buff, 1);
// 		}
// 		close(fds[0]);
// 	}
// 	else
// 	{
// 		close(fds[0]);
// 		write(fds[1], "servus\n", 7);
// 		close(fds[1]);
// 	}
// 	waitpid(pid, 0, 0);
// }
