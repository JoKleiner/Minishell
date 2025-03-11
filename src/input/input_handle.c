/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/11 10:14:10 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_arg(char *str, char ***args)
{
	int		i;
	int		u;
	char	**args_temp;

	i = 0;
	if (!str || !args)
		return (1);
	while ((*args)[i])
		i++;
	args_temp = malloc((i + 2) * sizeof(char *));
	if (!args_temp)
		return (free(str), 1);
	u = 0;
	while (u < i)
	{
		args_temp[u] = (*args)[u];
		u++;
	}
	args_temp[u] = str;
	args_temp[u + 1] = NULL;
	free(*args);
	*args = args_temp;
	return (0);
}

int	count_arg_len(char *input, int i, int *q_count)
{
	while (input[i] && !wh_space(input[i]) && !spez_char_wo_dol(input[i]))
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			(*q_count)++;
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
				i++;
			(*q_count)++;
		}
		i++;
	}
	return (i);
}

int	creat_args(char *input, int i, char ***args)
{
	int		i_temp;
	int		u;
	char	*str;
	int		q_count;

	i_temp = i;
	q_count = 0;
	i = count_arg_len(input, i, &q_count);
	str = malloc((i - i_temp - (q_count * 2)) + 1);
	if (!str)
		return (-1);
	u = 0;
	while (i_temp < i)
	{
		if (input[i_temp] == '\'')
		{
			i_temp++;
			while (input[i_temp] != '\'')
			{
				str[u] = input[i_temp];
				u++;
				i_temp++;
			}
			i_temp++;
			continue ;
		}
		if (input[i_temp] == '\"')
		{
			i_temp++;
			while (input[i_temp] != '\"')
			{
				str[u] = input[i_temp];
				u++;
				i_temp++;
			}
			i_temp++;
			continue ;
		}
		str[u] = input[i_temp];
		u++;
		i_temp++;
	}
	str[u] = '\0';
	if (add_arg(str, args) == 1)
		return (free(str), -1);
	return (i);
}

t_list	*new_stream(t_list *stream, t_list *stream_one)
{
	if (TOKEN->fd_out == STDOUT_FILENO)
		TOKEN->fd_out = 2;
	stream = stream_one;
	stream = init_stream(stream_one);
	TOKEN->fd_in = 2;
	return (stream);
}

int	handle_redir(int i, char *input, t_list *stream)
{
	while (wh_space(input[i]))
		i++;
	if (input[i] == '>')
	{
		i = redirect_out(input, i, stream);
	}
	else if (input[i] == '<')
	{
		i = redirect_in(input, i, stream);
	}
	return (i);
}

int	pipe_found(int i, t_list *stream_one, char ***args)
{
	t_list	*stream;
	char	**args_temp;

	args_temp = malloc(sizeof(char *));
	if(!args_temp)
		return(-1);
	args_temp[0] = NULL;
	stream = ft_lstlast(stream_one);
	TOKEN->arg = *args;
	stream = new_stream(stream, stream_one);
	*args = args_temp;
	return (i);
}

int	input_handle(char *input, t_list *stream_one)
{
	int		i;
	t_list	*stream;
	char	**args;

	i = 0;
	input = dollar_handle(input);
	stream = stream_one;
	args = malloc(sizeof(char *));
	if (!args)
		return (1);
	*args = NULL;
	while (input[i])
	{
		while (input[i] && wh_space(input[i]))
			i++;
		if (input[i] && (input[i] == '>' || input[i] == '<'))
			i = handle_redir(i, input, stream);
		else if (input[i] && input[i] == '|')
		{
			i = pipe_found(i, stream_one, &args);
			stream = ft_lstlast(stream_one);
		}
		else if (input[i])
		{
			i = creat_args(input, i, &args) - 1;
		}
		if (i == -1)
			return (1);
		i++;
	}
	if (args)
		TOKEN->arg = args;
	return (0);
}
