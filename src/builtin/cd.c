/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:22:23 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 10:32:24 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_path(char *path)
{
	char	*buf;
	char	*path_copy;
	char	*old_pwd;

	buf = NULL;
	path_copy = ft_strdup(path);
	old_pwd = getcwd(buf, 0);
	if (chdir(path_copy) != 0)
	{
		write(2, "cd: no such file or directory\n", 31);
		free(path_copy);
		return ;
	}
	add_t_item(ft_strjoin("OLDPWD=", old_pwd));
	buf = NULL;
	add_t_item(ft_strjoin("PWD=", getcwd(buf, 0)));
	free(buf);
	free(old_pwd);
	free(path_copy);
}

static void	change_to_old_path(t_link_cmds *cmd)
{
	if (ft_strlen(cmd->full_cmd[1]) != 1)
	{
		ft_printf("cd: no such file or directory: %s\n", cmd->full_cmd[1]);
		g_msh.error_code = 1;
	}
	else
		change_path(ht_search("OLDPWD"));
}

void	cd(t_link_cmds *cmd)
{
	if (cmd->count == 1)
		change_path(ht_search("HOME"));
	else if (cmd->count >= 3)
	{
		ft_printf("cd: too many arguments\n");
		g_msh.error_code = 1;
	}
	else if (cmd->full_cmd[1] && ft_strncmp(cmd->full_cmd[1], "-", 1) == 0)
		change_to_old_path(cmd);
	else
		change_path(cmd->full_cmd[1]);
}
