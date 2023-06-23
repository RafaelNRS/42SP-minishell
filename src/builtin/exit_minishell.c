/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:57:55 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:30:16 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *c)
{
	while (*c)
	{
		if (!ft_isdigit(*c++))
			return (FALSE);
	}
	return (TRUE);
}

void	exit_minishell()
{
	free_hash_table();
	exit(g_msh.error_code);
}

void	msh_exit(t_link_cmds *cmd)
{
	g_msh.error_code = 0;
	if (cmd->count >= 2 && !is_number(cmd->full_cmd[1]))
		msh_error(2, "exit", "numeric argument required");
	else if (cmd->count >= 3)
		msh_error(1, "exit", "too many arguments");
	else if (cmd->count == 2)
		g_msh.error_code = ft_atoi(cmd->full_cmd[1]);

	cleanup_chained_cmd(cmd);
	// free(cmd);
	// free_hash_table();
	// if (cmd_line)
	// 	free(cmd_line);
	exit_minishell();
}
