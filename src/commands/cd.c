/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/11 16:09:43 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exe_cd(t_list *stream)
{
	if (TOKEN->arg[1] != NULL && TOKEN->arg[2] != NULL)
		return (ft_error_cmd("Too many arguments!", "cd"));
	if (chdir(TOKEN->arg[1]) == -1)
		return(ft_error_cmd("Couldn't change directory.", "cd"));
}
