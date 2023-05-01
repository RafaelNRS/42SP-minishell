/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 13:07:10 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void echo(char **cmd)
// {
    // int i;
    // int has_flag;
    // int len;
    // int last_space;

    // i = 1;
    // has_flag = 0;
    // if (cmd[i])
    // {
    //     if (ft_strncmp(cmd[i], "-n", 3) == 0)
    //     {
    //         i++;
    //         has_flag++;
				// len = ft_strlen(cmd[i]);
				// if (ft_strncmp(cmd[i][len], " ", 1))
					// last_space = 1;
    //     }
    //     write(2, cmd[i], ft_strlen(cmd[i]));
    //     if (has_flag)
    //     {
	// 		if (last_space)

	// 		else
	// 			ft_printf(cmd[1]);
    //     }
    //     else
    // }
    // else
// }

void	built_in(TokenList *cmd, char *cmd_line)
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
	// // if (ft_strncmp(cmd->tokens[0], "echo\0", 5) == 0)
	// // 	echo(cmd);
	if (ft_strncmp(cmd->tokens[0], "cd\0", 3) == 0)
		cd(cmd);
}

void	execute(TokenList *cmd, char *cmd_line)
{
	built_in(cmd, cmd_line);
}
