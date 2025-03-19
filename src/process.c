/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:48 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 12:44:54 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	stream_handle(char *input, char ***copy_env, t_list *stream)
{
	int	fd;
	int	u;

	if (input_handle(input, stream, *copy_env))
		return (1);
	if (stream)
	{
		printf("\n");
		u = 0;
		printf("stream_num:%d\nfd_in:%d\nfd_out:%d\ninfile:%s\noutfile:%s\nhd_file:%s\n",
			TOKEN->stream_num, TOKEN->fd_in, TOKEN->fd_out, TOKEN->in_file,
			TOKEN->out_file, TOKEN->hd_file);
		if (TOKEN->arg)
			if (TOKEN->arg[u])
				while (TOKEN->arg[u])
				{
					ft_printf("arg[%d]:%s\n", u, TOKEN->arg[u]);
					u++;
				}
		printf("\n");
	}
	if (TOKEN->fd_in == -3)
	{
		fd = open(TOKEN->in_file, O_RDONLY);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
	}
	if (TOKEN->fd_in == -4)
	{
		fd = open(TOKEN->hd_file, O_RDONLY);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
	}
	ft_execute_command(stream, copy_env);
	return (0);
}

int	count_pipe(char *input)
{
	int		i;
	int		num_pipe;
	char	cha;

	i = 0;
	num_pipe = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			cha = input[i];
			i = skip_until_char(i, input, cha);
		}
		if (input[i] && input[i] == '|')
			num_pipe++;
		if (input[i])
			i++;
	}
	return (num_pipe);
}

int	search_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		if (input[i] == '|')
			return (1);
		if (input[i])
			i++;
	}
	return (0);
}

// return:
// 0 everything correct
// 1 error
int	start_process(char *input, t_list *stream_one, char **copy_env)
{
	t_list	*stream;
	int		num_pipe;
	int		i;
	int		u;
	int		fds[2];
	int		pid;
	int		error_num;
	int		std_in;
	int		pipes;
	int		pipe_error;
	int		status;

	num_pipe = count_pipe(input);
	i = 0;
	u = 0;
	status = 0;
	if (search_pipe(input))
	{
		pid = fork();
		if (pid == -1)
			return (write(1, "error\n", 6), 1);
		if (pid == 0)
		{
			stream_one = init_stream(NULL);
			if (stream_one == NULL)
				return (free(input), write(1, "error\n", 6), 1);
			stream = stream_one;
			while (i <= num_pipe)
			{
				if (pid == 0 && i != num_pipe)
				{
					pipe_error = pipe(fds);
					pid = fork();
					if (pipe_error == -1 || pid == -1)
						return (write(1, "error\n", 6));
					if (pid == 0)
					{
						close(fds[WR_IN]);
						dup2(fds[RD_OUT], STDIN_FILENO);
						close(fds[RD_OUT]);
						stream = init_stream(stream_one);
						if (stream == NULL)
							return (free(input), write(1, "errorasd\n", 16), 1);
						TOKEN->fd_in = fds[RD_OUT];
					}
					else
					{
						close(fds[RD_OUT]);
						TOKEN->fd_out = fds[WR_IN];
						pipes = 0;
						while (pipes < i)
						{
							if (input[u] == '|')
								pipes++;
							u++;
						}
						input = stream_input(input, u);
						error_num = stream_handle(input, &copy_env, stream);
						if (error_num == 1)
							return (1);
						close(fds[WR_IN]);
						waitpid(pid, &status, 0);
						exit(status);
					}
				}
				else
				{
					pipes = 0;
					while (pipes < i)
					{
						if (input[u] == '|')
							pipes++;
						u++;
					}
					input = stream_input(input, u);
					error_num = stream_handle(input, &copy_env, stream);
					if (error_num == 1)
						return (1);
					exit(0);
				}
				i++;
			}
		}
		waitpid(pid, &status, 0);
	}
	else
	{
		std_in = dup(STDIN_FILENO);
		stream_one = init_stream(NULL);
		if (stream_one == NULL)
			return (free(input), write(1, "error\n", 6), 1);
		stream = stream_one;
		error_num = stream_handle(input, &copy_env, stream);
		if (error_num == 1)
			return (1);
		dup2(std_in, STDIN_FILENO);
		// if (error_num == 1)
		// 	return (1);
		// free_stream(stream_one);
	}
	return (status);
}
