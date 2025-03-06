/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:43:35 by joklein           #+#    #+#             */
/*   Updated: 2025/03/06 12:28:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	dollar_found(int i, char *input, t_list *stream)
// {
// 	int	i_temp;
// 	int	u;

// 	u = 0;
// 	while (!wh_space(input[i]) && input[i])
// 	{
// 		i++;
// 		u++;
// 	}
// 	str = ft_strndup(&input[i_temp + 1], u);
// 	u = 0;
// 	while (TOKEN->envp[u])
// 	{
// 		if (ft_strncmp(str, TOKEN->envp[u], ft_strlen(str)) == 0)
// 			break ;
// 		u++;
// 	}
// 	if (TOKEN->envp[u] && i != i_temp + 1)
// 	{
// 		printf("%s\n", TOKEN->envp[u]);
// 		change_input();
// 	}
// 	else
// 	{
// 	}
// 	return (i);
// }

// char	*dollar_handle(char *input, t_list *stream)
// {
// 	char	*str;
// 	int		i;
// 	int		i_temp;

// 	i = 0;
// 	while (input[i])
// 	{
// 		while (input[i] != '$' && input[i])
// 			i++;
// 		if (input[i] == '$')
// 		{
// 			if (i >= 2)
// 			{
// 				i_temp = i;
// 				while (i_temp > 2 && wh_space(input[i_temp - 1]))
// 					i_temp--;
// 				if (input[i_temp - 1] == '<' && input[i_temp - 2] == '<')
// 					while (!wh_space(input[i]) && input[i])
// 						i++;
// 			}
// 			i = dollar_found(i, input, stream);
// 		}
// 	}
// 	return (input);
// }
