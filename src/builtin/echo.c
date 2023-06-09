/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:09:25 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 20:57:36 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_link_cmds	*cmd, bool has_flag_n, int i)
{
	char	**current;

	current = cmd->full_cmd;
	if (cmd->count > 1 && cmd->full_cmd[1])
	{
		has_flag_n = 0;
		if (ft_strncmp(current[i], "-n", 2) == 0 && ft_strlen(current[i]) == 2)
		{
			has_flag_n = TRUE;
			i++;
		}
		while (current[i])
		{
			if (current[i + 1] == NULL && has_flag_n)
				ft_printf("%s", current[i]);
			else if (current[i + 1] == NULL)
				ft_printf("%s\n", current[i]);
			else
				ft_printf("%s ", current[i]);
			i++;
		}
	}
	else
		ft_printf("\n");
}
