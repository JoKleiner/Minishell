/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:04:01 by joklein           #+#    #+#             */
/*   Updated: 2025/03/21 12:20:10 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_init_stream(t_list *stream_one, t_list *stream, int ori_sdtin)
{
	int	i;

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
	TOKEN->error = 0;
	TOKEN->ori_sdtin = ori_sdtin;
}

t_list	*init_stream(t_list *stream_one, int ori_sdtin)
{
	t_list	*stream;
	t_token	*stream_info;

	stream_info = (t_token *)malloc(sizeof(t_token));
	if (!stream_info)
		return (NULL);
	stream = ft_lstnew(stream_info);
	if (!stream)
		return (free(stream_info), (NULL));
	ft_lstadd_back(&stream_one, stream);
	set_init_stream(stream_one, stream, ori_sdtin);
	return (stream);
}

char	*stream_input(char *input, int u)
{
	char	*input_new;

	input_new = ft_strdup(&input[u]);
	free(input);
	return (input_new);
}
