/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:04:01 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 14:04:16 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_init_stream(t_token *stream, int ori_sdtin, int num_pipes)
{
	int	i;

	i = 0;
	stream->stream_num = num_pipes;
	stream->fd_in = STDIN_FILENO;
	stream->fd_out = STDOUT_FILENO;
	stream->in_file = NULL;
	stream->out_file = NULL;
	stream->arg = NULL;
	stream->hd_file = NULL;
	stream->error = 0;
	stream->ori_sdtin = ori_sdtin;
	stream->copy_env = NULL;
}

t_token	*init_stream(t_token *stream, int ori_sdtin, int num_pipes)
{
	stream = (t_token *)malloc(sizeof(t_token));
	if (!stream)
		return (NULL);
	set_init_stream(stream, ori_sdtin, num_pipes);
	return (stream);
}

char	*stream_input(char *input, int u)
{
	char	*input_new;

	input_new = ft_strdup(&input[u]);
	free(input);
	return (input_new);
}
