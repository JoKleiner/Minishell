/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:04:01 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 11:04:17 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*stream_input(char *input, int u)
{
	char	*input_new;

	input_new = ft_strdup(&input[u]);
	free(input);
	return (input_new);
}
