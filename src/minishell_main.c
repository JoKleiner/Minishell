/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/21 17:32:56 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_value(int num)
{
	static int	return_num;
	int			return_num_temp;

	return_num = 0;
	return_num_temp = return_num;
	return_num = num;
	return (return_num_temp);
}

char	*get_input(void)
{
	char	*line;
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("\033[0;34mminishell> \033[0m");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

int	main(void)
{
	char	**copy_env;
	char	*input;
	int		return_num;

	return_num = 0;
	setup_signals();
	copy_env = ft_init_envvars();
	if (!copy_env)
		return (ft_errmal("Error: minishell: "), 1);
	while (1)
	{
		input = get_input();
		if (!input && isatty(STDIN_FILENO))
			return (free_strarr(copy_env), rl_clear_history(), \
			write(1,"exit\n", 5), return_num);
		else if (!input)
			return (free_strarr(copy_env), rl_clear_history(), return_num);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (check_syntax(input) == 1)
			continue ;
		return_num = return_value(start_process(input, &copy_env));
	}
}
