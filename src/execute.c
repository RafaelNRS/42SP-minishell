/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/09 22:41:33 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_link_cmds	*cmd)
{
	if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		export(cmd);
	if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		unset(cmd);
	if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		env();
	if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		pwd(cmd);
	// if (ft_strncmp(cmd->cmd "exit\0", 5) == 0)
	// 	exit_minishell();
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		echo(cmd);

}
