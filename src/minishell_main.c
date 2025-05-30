/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:35 by joklein           #+#    #+#             */
/*   Updated: 2025/04/01 19:16:32 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_value(int num, bool set_num)
{
	static int	return_num = 0;

	if (set_num == true)
		return_num = num;
	return (return_num);
}

char	*get_input(void)
{
	char	*line;
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("minishell> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

int	heredoc_handle(char *input, char **copy_env)
{
	int	i;
	int	num_pipes;
	int	num_ret;

	i = 0;
	num_pipes = 0;
	num_ret = 0;
	while (input[i])
	{
		if (input[i] == '|')
			num_pipes++;
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			num_ret = (heredoc(&i, input, copy_env, num_pipes));
		}
		if (num_ret != 0)
			return (num_ret);
		i++;
	}
	return (0);
}

int	syn_hered_process(char *input, char ***copy_env)
{
	int	num_ret;
	int	std_in;

	num_ret = check_syntax(input);
	if (num_ret != 0)
		return (num_ret);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1)
		return (ft_errmal("dup failed"), 1);
	num_ret = heredoc_handle(input, *copy_env);
	if (dup2(std_in, STDIN_FILENO) == -1)
		return (close(std_in), ft_errmal("dup2 failed"), 1);
	close(std_in);
	if (num_ret != 0)
		return (num_ret);
	num_ret = start_process(input, copy_env);
	setup_signals();
	if (g_sig == 1)
		printf("\n");
	if (g_sig == 2)
		printf("Quit: 3\n");
	g_sig = 0;
	return (num_ret);
}

int	main(void)
{
	char	**copy_env;
	char	*input;
	int		num_ret;

	num_ret = 0;
	copy_env = ft_init_envvars();
	if (!copy_env)
		return (ft_errmal("Error: minishell: "), 1);
	setup_signals();
	while (1)
	{
		input = get_input();
		if (!input && isatty(STDIN_FILENO))
			return (free_strarr(copy_env), rl_clear_history(), write(1,
					"exit\n", 5), num_ret);
		else if (!input)
			return (free_strarr(copy_env), rl_clear_history(), num_ret);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		num_ret = (return_value(syn_hered_process(input, &copy_env), true));
	}
}
