/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:09:25 by mariana           #+#    #+#             */
/*   Updated: 2023/05/13 11:59:50 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(TokenList *cmd)
{
	int	i;
	int	has_flag_n;

	if (cmd->count > 1)
	{
		i = 1;
		has_flag_n = 0;
		if (ft_strncmp(cmd->tokens[i], "-n", 2) == 0
			&& ft_strlen(cmd->tokens[i]) == 2)
		{
			has_flag_n++;
			i++;
		}
		while (i < cmd->count)
		{
			if (i == cmd->count - 1 && has_flag_n)
				ft_printf("%s", cmd->tokens[i]);
			else if (i == cmd->count - 1)
				ft_printf("%s\n", cmd->tokens[i]);
			else
				ft_printf("%s ", cmd->tokens[i]);
			i++;
		}
	}
}
