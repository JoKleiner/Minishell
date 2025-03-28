/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:29:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 12:17:39 by mpoplow          ###   ########.fr       */
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

void	free_content(t_list *stream)
{
	if (TOKEN->arg)
		free_strarr(TOKEN->arg);
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	if (TOKEN->out_file)
		free(TOKEN->out_file);
	if (TOKEN->fd_out != STDOUT_FILENO)
		close(TOKEN->fd_out);
	if (TOKEN->hd_file)
	{
		unlink(TOKEN->hd_file);
		free(TOKEN->hd_file);
	}
}

void	free_stream(t_list *stream)
{
	free_content(stream);
	free(stream->cont);
	free(stream);
}
