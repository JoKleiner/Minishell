/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 12:20:48 by mpoplow          ###   ########.fr       */
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

char	*stream_input(char *input, int u)
{
	char	*input_new;

	input_new = ft_strdup(&input[u]);
	free(input);
	return (input_new);
}

int	stream_handle(char *input, char ***copy_env, t_list *stream)
{
	int	u;
	int	fd;

	if (input_handle(input, stream, *copy_env))
		return (1);
	if (stream)
	{
		ft_printf("\n");
		u = 0;
		ft_printf("stream_num:%d\nfd_in:%d\nfd_out:%d\ninfile:%s\noutfile:%s\nhd_file:%s\n",
					TOKEN->stream_num,
					TOKEN->fd_in,
					TOKEN->fd_out,
					TOKEN->in_file,
					TOKEN->out_file,
					TOKEN->hd_file);
		if (TOKEN->arg)
			if (TOKEN->arg[u])
				while (TOKEN->arg[u])
				{
					ft_printf("arg[%d]:%s\n", u, TOKEN->arg[u]);
					u++;
				}
		ft_printf("\n");
	}
	if (TOKEN->fd_in != STDIN_FILENO)
	{
		if (TOKEN->fd_in == 3)
			fd = open(TOKEN->in_file, O_RDONLY);
		if (TOKEN->fd_in == 4)
			fd = open(TOKEN->hd_file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	ft_execute_command(stream, copy_env);
	return (0);
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

int	main(void)
{
	t_list	*stream_one;
	t_list	*stream;
	char	**copy_env;
	char	*input;
	int		num_pipe;
	char	syn_char;
	int		pipes;
	int		pipe_error;
	int		i;
	int		u;
	int		fds[2];
	int		pid;
	int		error_num;
	int		std_in;

	setup_signals();
	copy_env = ft_strarrdup(environ);
	if (!copy_env)
		return (ft_errmal("Error: minishell: "), 1);
	stream_one = NULL;
	while (1)
	{
		input = readline("\033[0;34mminishell> \033[0m");
		if (!input)
			return (free_strarr(copy_env), rl_clear_history(), write(1,
					"exit\n", 5), 1);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		syn_char = check_syntax(input);
		if (syn_char != '\0')
		{
			ft_printf("syntax error near unexpected token `%c'", syn_char);
			free(input);
			continue ;
		}
		num_pipe = count_pipe(input);
		i = 0;
		u = 0;
		if (search_pipe(input))
		{
			pid = fork();
			if (pid == -1)
				return (write(1, "error\n", 6));
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
							stream = init_stream(stream_one);
							if (stream == NULL)
								return (free(input), write(1, "errorasd\n", 16),
									1);
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
							waitpid(pid, 0, 0);
							return (0);
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
						return (0);
					}
					i++;
				}
			}
			waitpid(pid, 0, 0);
		}
		else
		{
			std_in = dup(STDIN_FILENO);
			stream_one = init_stream(NULL);
			if (stream_one == NULL)
				return (free(input), write(1, "error\n", 6), 1);
			stream = stream_one;
			error_num = stream_handle(input, &copy_env, stream);
			dup2(std_in, STDIN_FILENO);
			// if (error_num == 1)
			// 	return (1);
			// free_stream(stream_one);
		}
	}
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
