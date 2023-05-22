/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/05/22 17:00:00 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_token_list *cmd)
{
	if (ft_strncmp(cmd->head->token, "export\0", 7) == 0)
		export(cmd);
	if (ft_strncmp(cmd->head->token, "unset\0", 6) == 0)
		unset(cmd);
	if (ft_strncmp(cmd->head->token, "env\0", 4) == 0)
		env();
	if (ft_strncmp(cmd->head->token, "pwd\0", 4) == 0)
		pwd(cmd);
	if (ft_strncmp(cmd->head->token, "exit\0", 5) == 0)
		exit_minishell();
	if (ft_strncmp(cmd->head->token, "echo\0", 5) == 0)
		echo(cmd);
	if (ft_strncmp(cmd->head->token, "cd\0", 3) == 0)
		cd(cmd);
}
