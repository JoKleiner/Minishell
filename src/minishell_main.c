/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/07 11:47:29 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int wh_space(char input)
{
    if (input == ' ' || input == '\t' || input == '\n')
        return (1);
    return (0);
}
int wr_symbol(char input)
{
    if (input == '<' || input == '>')
        return (1);
    if (input == '|' || input == '$')
        return (1);
    return (0);
}

t_list	*init_stream(t_list *stream_one)
{
	t_list	*stream;
	t_token	*stream_info;
	int		i;

	stream_info = (t_token *)malloc(sizeof(t_token));
	if (!stream_info)
		return (NULL);
	stream = ft_lstnew(stream_info);
	ft_lstadd_back(&stream_one, stream);
	i = 1;
	stream = stream_one;
	while (stream->next)
	{
		i++;
		stream = stream->next;
	}
	TOKEN->stream_num = i;
	TOKEN->fd_in = 1;
	TOKEN->fd_out = 1;
	TOKEN->in_file = NULL;
	TOKEN->out_file = NULL;
	TOKEN->arg = NULL;
	TOKEN->add = false;
	return (stream);
}

int	main(void)
{
	char	*input;
	t_list	*stream_one;
	t_list	*stream;
	int		i;
	int		u;

	while (1)
	{
		stream_one = NULL;
		input = readline("minishell> ");
		if (!input)
			return (free(input), write(1, "exit\n", 5), 0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_one = init_stream(stream_one);
		if (stream_one == NULL)
			return (free(input), 0);
		i = input_handle(input, stream_one);
		if (i == 1)
			return (1);
		stream = stream_one;
		u = 1;
		while (stream)
		{
			if (TOKEN->arg)
			{
				ft_printf("\n");
				i = 0;
				ft_printf("Stream: %d\nfd_in: %d\nfd_out:%d\ninfile:%s\noutfile:%s\nadd: %d\n",
						TOKEN->stream_num, TOKEN->fd_in, TOKEN->fd_out,
						TOKEN->in_file,TOKEN->out_file,TOKEN->add);
				while (TOKEN->arg[i])
				{
					ft_printf("arg[%d]:%s\n", i, TOKEN->arg[i]);
					i++;
				}
				ft_printf("\n");
			}
			stream = stream->next;
			u++;
		}
		ft_execute_command(stream_one);
		free(input);
	}
	return (0);
}
