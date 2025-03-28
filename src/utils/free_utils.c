/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:29:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 14:22:46 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_strarr(char **sstr)
{
	int	i;

	i = 0;
	if (sstr)
	{
		while (sstr[i])
			free(sstr[i++]);
		free(sstr);
	}
}

void	free_content(t_token *stream)
{
	if (stream->arg)
		free_strarr(stream->arg);
	if (stream->in_file)
		free(stream->in_file);
	if (stream->out_file)
		free(stream->out_file);
	if (stream->fd_out != STDOUT_FILENO)
		close(stream->fd_out);
	if (stream->hd_file)
	{
		unlink(stream->hd_file);
		free(stream->hd_file);
	}
}

void	free_stream(t_token *stream)
{
	free_content(stream);
	free(stream);
}
