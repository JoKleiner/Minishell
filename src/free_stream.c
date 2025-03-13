/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:29:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/11 15:37:46 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_strstr(char **sstr)
{
	int	i;

	i = 0;
	while (sstr[i])
		free(sstr[i++]);
	if (sstr)
		free(sstr);
}

void	free_stream(t_list *stream)
{
	t_list	*stream_next;

	while (stream->next)
	{
		stream_next = stream->next;
		free(stream->cont);
		free(stream);
		stream = stream_next;
	}
	free(stream->cont);
	free(stream);
}
