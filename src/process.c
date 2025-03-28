/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:48 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 18:54:18 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_debug_print_stream(t_token *stream)
// {
// 	int	u;

// 	if (stream)
// 	{
// 		printf("\n");
// 		u = 0;
// 		printf("stream_num:%d\nfd_in:%d\nfd_out:%d\n", stream->stream_num,
// 			stream->fd_in, stream->fd_out);
// 		printf("infile:%s\noutfile:%s\nhd_file:%s\n", stream->in_file,
// 			stream->out_file, stream->hd_file);
// 		if (stream->arg)
// 			if (stream->arg[u])
// 				while (stream->arg[u])
// 				{
// 					printf("arg[%d]:%s\n", u, stream->arg[u]);
// 					u++;
// 				}
// 		printf("\n");
// 	}
// }

int	stream_handle(char *input, char ***copy_env, t_token *stream)
{
	int		return_num;
	int		i;
	char	*input_new;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && i > 1 && input[i - 1] != '>')
			break ;
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	input_new = ft_strndup(input, i);
	if (!input_new)
		return (mem_fail(stream), stream->error);
	return_num = input_handle(input_new, stream, *copy_env);
	if (return_num != 0)
		return (return_num);
	if (set_fd_in(stream) != 0)
		return (1);
	ft_execute_command(stream, copy_env);
	return_num = stream->error;
	return (return_num);
}

static int	count_pipe(char *input)
{
	int	i;
	int	num_pipe;

	i = 0;
	num_pipe = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		if (input[i] == '>' && input[i + 1] == '|')
			i += 2;
		if (input[i] && input[i] == '|')
			num_pipe++;
		if (input[i])
			i++;
	}
	return (num_pipe);
}

int	no_pipe_process(char *input, char ***copy_env, int ori_sdtin)
{
	t_token	*stream;
	int		std_in;
	int		return_num;

	stream = init_stream(NULL, ori_sdtin, 0);
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
	int	num_pipe;
	int	ori_sdtin;
	int	status;

	ori_sdtin = dup(STDIN_FILENO);
	if (ori_sdtin == -1)
	{
		ft_errmal("fork failed");
		return (errno);
	}
	num_pipe = count_pipe(input);
	status = 0;
	if (num_pipe != 0)
		status = pipe_handle(num_pipe, ori_sdtin, input, copy_env);
	else
		return (no_pipe_process(input, copy_env, ori_sdtin));
	return (status);
}
