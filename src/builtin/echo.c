/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:09:25 by mariana           #+#    #+#             */
/*   Updated: 2023/06/14 21:51:26 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_link_cmds	*cmd)
{
	int		has_flag_n;
	char	**current;
	int		i;

	i = 1;
	current = cmd->full_cmd;
	if (cmd->count > 1)
	{
		has_flag_n = 0;
		if (ft_strncmp(current[i], "-n", 2) == 0 && ft_strlen(current[i]) == 2)
		{
			has_flag_n++;
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
}
