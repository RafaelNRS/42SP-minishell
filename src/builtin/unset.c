/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:02:35 by mariana           #+#    #+#             */
/*   Updated: 2023/06/09 22:32:32 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_link_cmds	*var)
{
	char **var_name;
	int i;

	i = 1;
	var_name = var->full_cmd;
	while (var_name[i])
	{
		delete_item(var_name[i]);
		i++;
	}
}
