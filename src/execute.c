/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/05/20 11:26:43 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_tk_lst *cmd)
{
	if (ft_strncmp(cmd->tokens[0], "export\0", 7) == 0)
		export(cmd);
	if (ft_strncmp(cmd->tokens[0], "unset\0", 6) == 0)
		unset(cmd);
	if (ft_strncmp(cmd->tokens[0], "env\0", 4) == 0)
		env();
	if (ft_strncmp(cmd->tokens[0], "pwd\0", 4) == 0)
		pwd(cmd);
	if (ft_strncmp(cmd->tokens[0], "exit\0", 5) == 0)
		exit_minishell();
	if (ft_strncmp(cmd->tokens[0], "echo\0", 5) == 0)
		echo(cmd);
	if (ft_strncmp(cmd->tokens[0], "cd\0", 3) == 0)
		cd(cmd);
}
