/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/18 10:10:55 by joklein          ###   ########.fr       */
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

int	handle_redir(int i, char *input, t_list *stream, char **copy_env)
{
	if (input[i] == '>')
		i = redirect_out(input, i, stream);
	else if (input[i] == '<')
	{
		i = redirect_in(input, i, stream, copy_env);
	}
	return (i);
}

int	input_handle(char *input, t_list *stream, char	**copy_env)
{
	int		i;
	
	
	input = dollar_handle(input, copy_env);
	if (!input)
		return (1);
	i = -1;
	while (input[++i])
	{
		if (wh_space(input[i]))
			sleep(0);
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redir(i, input, stream, copy_env);
		else if (input[i] == '|')
			return(0);
		else
			i = creat_args(input, i, stream);
		if (i == -1)
			return (free(input), 1);
	}
	return (0);
}
