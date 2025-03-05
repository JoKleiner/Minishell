/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/04 17:53:14 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_stream(t_list *stream_one)
{
	t_list	*stream;
	t_token	*stream_info;

	stream_info = (t_token *)malloc(sizeof(t_token));
	if (!stream_info)
		return (NULL);
	stream = ft_lstnew(stream_info);
	TOKEN->input = 1;
	TOKEN->output = 1;
	TOKEN->in_file = NULL;
	TOKEN->out_file = NULL;
	TOKEN->cmd = NULL;
	TOKEN->arg = NULL;
	TOKEN->add = 0;
	ft_lstadd_back(&stream_one, stream);
	return (stream);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*stream_one;
	t_list	*stream;
	char	**args;
	int		i;
	int		u;

	(void)argc;
	(void)argv;
	(void)envp;
	stream_one = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (free(input), write(1, "exit", 4), 0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_one = init_stream(stream_one);
		if (stream_one == NULL)
			return (free(input), 0);
		args = input_handle(input, stream_one);
		stream = stream_one;
		u = 1;
		while (stream)
		{
			if (args)
			{
				ft_printf("\n");
				i = 0;
				ft_printf("Stream: %d\ninput:%d\noutput:%d\ninfile:%s\noutfile:%s\ncmd:%s\nadd:%d\n", u,
					TOKEN->input, TOKEN->output, TOKEN->in_file,
					TOKEN->out_file, TOKEN->cmd, TOKEN->add);
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
		execute_command(stream_one, envp);
		free(input);
		free(args);
	}
	return (0);
}
