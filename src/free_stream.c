/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:29:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/11 10:34:51 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
