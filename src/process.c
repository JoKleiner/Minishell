/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:48 by joklein           #+#    #+#             */
/*   Updated: 2025/03/24 11:57:18 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_stream(t_list *stream)
{
	int	u;

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
}

int	stream_handle(char *input, char ***copy_env, t_list *stream)
{
	int	fd;
	int	return_num;

	return_num = input_handle(input, stream, *copy_env);
	if (return_num != 0)
		return (return_num);
	//ft_print_stream(stream);
	if (TOKEN->fd_in == -3 || TOKEN->fd_in == -4)
	{
		if (TOKEN->fd_in == -3)
			fd = open(TOKEN->in_file, O_RDONLY);
		if (TOKEN->fd_in == -4)
			fd = open(TOKEN->hd_file, O_RDONLY);
		if (fd == -1)
			return (ft_errmal("open failed"), errno);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (ft_errmal("dup2 failed"), errno);
	}
	ft_execute_command(stream, copy_env);
	return_num = TOKEN->error;
	return (return_num);
}

int	count_pipe(char *input)
{
	int		i;
	int		num_pipe;

	i = 0;
	num_pipe = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		if (input[i] && input[i] == '|')
			num_pipe++;
		if (input[i])
			i++;
	}
	return (num_pipe);
}

int	no_pipe_process(char *input, char ***copy_env, int ori_sdtin)
{
	t_list	*stream;
	int		std_in;
	int		return_num;

	stream = init_stream(NULL, ori_sdtin);
	if (stream == NULL)
		return (free(input), ft_errmal("malloc failed"), ENOMEM);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1)
		return (free(input), free_stream(stream), ft_errmal("dup failed"),
			errno);
	return_num = stream_handle(input, copy_env, stream);
	free_stream(stream);
	if (dup2(std_in, STDIN_FILENO) == -1)
		return (ft_errmal("dup2 failed"), errno);
	return (return_num);
}

int	start_process(char *input, char ***copy_env)
{
	t_list	*stream_one;
	t_list	*stream;
	int		num_pipe;
	int		i;
	int		u;
	int		fds[2];
	int		pid;
	int		pipes;
	int		pipe_error;
	int		status;
	int		ori_sdtin;

	ori_sdtin = dup(STDIN_FILENO);
	if (ori_sdtin == -1)
	{
        ft_errmal("fork failed");
        return (errno);
    }
	num_pipe = count_pipe(input);
	i = 0;
	u = 0;
	status = 0;
	stream_one = NULL;
	if (num_pipe != 0)
	{
		pid = fork();
		if (pid == -1)
			return (ft_errmal("fork failed"), 1);
		if (pid == 0)
		{
			stream_one = init_stream(NULL, ori_sdtin);
			if (stream_one == NULL)
			{
				free(input);
				write(1, "error\n", 6);
				exit(1);
			}
			stream = stream_one;
			while (i <= num_pipe)
			{
				if (pid == 0 && i != num_pipe)
				{
					pipe_error = pipe(fds);
					pid = fork();
					if (pipe_error == -1 || pid == -1)
					{
						free(input);
						write(1, "error\n", 6);
						exit(1);
					}
					if (pid == 0)
					{
						close(fds[WR_IN]);
						dup2(fds[RD_OUT], STDIN_FILENO);
						close(fds[RD_OUT]);
						stream = init_stream(NULL, ori_sdtin);
						if (stream == NULL)
						{
							free(input);
							write(1, "error\n", 6);
							exit(1);
						}
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
						stream_handle(input, copy_env, stream);
						if (TOKEN->error == 1)
							exit(1);
						close(fds[WR_IN]);
						waitpid(pid, &status, 0);
						free_stream(stream);
						exit(WEXITSTATUS(status));
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
					stream_handle(input, copy_env, stream);
					if (TOKEN->error == 1)
						exit(1);
					free_stream(stream);
					exit(0);
				}
				i++;
			}
		}
		waitpid(pid, &status, 0);
	}
	else
		return (no_pipe_process(input, copy_env, ori_sdtin));
	return (WEXITSTATUS(status));
}
