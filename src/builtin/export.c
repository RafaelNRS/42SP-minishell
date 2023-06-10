/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:01:54 by mariana           #+#    #+#             */
/*   Updated: 2023/06/09 22:27:02 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_link_cmds	*var)
{
	char **command;
	int i;

	i = 1;
	command = var->full_cmd;
	while (command[i])
	{
		if (ft_strchr(command[i], '='))
			add_t_item(command[i]);
		i++;
	}
}
