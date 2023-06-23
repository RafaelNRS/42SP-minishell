/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:02:35 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:30:35 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_link_cmds	*var)
{
	char	**var_name;
	int		i;

	g_msh.error_code = 0;
	i = 1;
	var_name = var->full_cmd;
	while (var_name[i])
	{
		delete_item(var_name[i]);
		i++;
	}
}
