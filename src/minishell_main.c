/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/06 12:28:37 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

int	wr_symbol(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '$')
		return (1);
	return (0);
}

t_list	*init_stream(t_list *stream_one, char **envp)
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
	TOKEN->envp = envp;
	ft_lstadd_back(&stream_one, stream);
	return (stream);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*stream_one;
	t_list	*stream;
	int		i;
	int		u;

	(void)argc;
	(void)argv;
	stream_one = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (free(input), write(1, "exit\n", 5), 0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		stream_one = init_stream(stream_one, envp);
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
				ft_printf("Stream: %d\ninput: %d\noutput:%d\ninfile:%s\noutfile: %s\ncmd: %s\nadd: %d\n", u,
					TOKEN->input, TOKEN->output, TOKEN->in_file,TOKEN->out_file, TOKEN->cmd, TOKEN->add);
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
		//ft_execute_command(stream_one, envp);
		free(input);
	}
	return (0);
}
