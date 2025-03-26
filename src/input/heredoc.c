/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:51:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/26 17:56:24 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*init_heredoc(int num_pipes)
{
	int		fd;
	char	*here_doc;
	char	*num_str;

	num_str = ft_itoa(num_pipes);
	if (!num_str)
		return (ft_errmal("Malloc failed."), NULL);
	here_doc = ft_strjoin(".heredoc", num_str);
	if (!here_doc)
		return (free(num_str), ft_errmal("Malloc failed."), NULL);
	free(num_str);
	fd = open(here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(here_doc), ft_errmal("open failed"), NULL);
	close(fd);
	return (here_doc);
}

static int	create_heredoc(char *str, char **copy_env, int num_pipes)
{
	char	*here_doc;
	int		num_ret;

	here_doc = init_heredoc(num_pipes);
	if (!here_doc)
		return (free(str), errno);
	num_ret = heredoc_child_process(str, here_doc, copy_env);
	setup_signals();
	return (num_ret);
}

int	heredoc(int *i, char *input, char **copy_env, int num_pipes)
{
	int		i_temp;
	int		i_temp2;
	char	*str;

	i_temp = (*i);
	while (input[i_temp] && wh_space(input[i_temp]))
		i_temp++;
	i_temp2 = i_temp;
	while (input[i_temp] && !wh_space(input[i_temp])
		&& !spec_char(input[i_temp]))
	{
		if (input[i_temp] == '\'' || input[i_temp] == '\"')
			i_temp = skip_until_char(i_temp, input, input[i_temp]);
		i_temp++;
	}
	str = str_quote_less(&input[i_temp2], i_temp - i_temp2);
	if (!str)
		return (ft_errmal("Malloc failed."), ENOMEM);
	return (create_heredoc(str, copy_env, num_pipes));
}
