/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 11:05:56 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_found(int i, t_list *stream_one)
{
	t_list	*stream;

	stream = ft_lstlast(stream_one);
	if (TOKEN->fd_out == STDOUT_FILENO)
		TOKEN->fd_out = 2;
	stream = init_stream(stream_one);
	if (!stream)
		return (-1);
	TOKEN->fd_in = 2;
	return (i);
}

int	handle_redir(int i, char *input, t_list *stream)
{
	if (input[i] == '>')
		i = redirect_out(input, i, stream);
	else if (input[i] == '<')
	{
		i = redirect_in(input, i, stream);
	}
	return (i);
}

int	input_handle(char *input, t_list *stream_one)
{
	int		i;
	t_list	*stream;

	input = dollar_handle(input);
	if (!input)
		return (1);
	stream = stream_one;
	i = -1;
	while (input[++i])
	{
		if (wh_space(input[i]))
			sleep(0);
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redir(i, input, stream);
		else if (input[i] == '|')
		{
			i = pipe_found(i, stream_one);
			stream = ft_lstlast(stream_one);
		}
		else
			i = creat_args(input, i, stream);
		if (i == -1)
			return (free(input), 1);
	}
	return (free(input), 0);
}
