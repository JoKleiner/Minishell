/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 12:58:34 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

int	spec_char(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '$')
		return (1);
	return (0);
}

int	spec_char_wo_dol(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|')
		return (1);
	return (0);
}

int	return_value(int num)
{
	static int	return_num = 0;
	int			return_num_temp;

	return_num_temp = return_num;
	return_num = num;
	return (return_num_temp);
}

int	main(void)
{
	t_list	*stream_one;
	char	**copy_env;
	char	*input;
	char	*syn_str;
	char	*line;
	int		return_num;

	setup_signals();
	copy_env = ft_strarrdup(environ);
	if (!copy_env)
		return (ft_errmal("Error: minishell: "), 1);
	stream_one = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("\033[0;34mminishell> \033[0m");
		else
		{
			line = get_next_line(STDIN_FILENO);
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input && isatty(STDIN_FILENO))
			return (free_strarr(copy_env), rl_clear_history(), write(1,
					"exit\n", 5), 1);
		else if (!input)
			return (free_strarr(copy_env), rl_clear_history(), 1);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		syn_str = check_syntax(input);
		if (syn_str != NULL)
		{
			ft_printf("syntax error near unexpected token `%s'", syn_str);
			free(input);
			continue ;
		}
		return_num = start_process(input, stream_one, copy_env);
		return_value(return_num);
	}
	free_strarr(copy_env);
	rl_clear_history();
	return (0);
}
