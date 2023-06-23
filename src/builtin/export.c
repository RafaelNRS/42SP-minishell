/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:01:54 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:30:26 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_link_cmds	*var)
{
	char	**command;
	int		i;

	g_msh.error_code = 0;
	i = 1;
	command = var->full_cmd;
	while (command[i])
	{
		if (ft_strchr(command[i], '='))
			add_t_item(command[i]);
		i++;
	}
}
