/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:22:23 by mariana           #+#    #+#             */
/*   Updated: 2023/06/22 00:37:12 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_paths(char *path)
{
	int		pid;
	char	*old_path;
	char	*pwd;

	pid = fork();
	if (pid == -1)
		ft_printf("Error: Fork\n");
	if (pid == 0)
		old_path = ft_strjoin("OLDPWD=", ht_search("PWD"));
	waitpid(pid, NULL, 0);
	pid = fork();
	if (pid == -1)
		ft_printf("Error: Fork\n");
	if (pid == 0)
		pwd = ft_strjoin("PWD=", path);
	waitpid(pid, NULL, 0);
	add_t_item(old_path);
	add_t_item(pwd);
	free(old_path);
	free(pwd);
}

void	change_path(char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		update_paths(path);
	}
	else
		ft_printf("cd: no such file or directory: %s\n", path);
}

void	change_to_old_path(t_link_cmds *cmd)
{
	if (cmd->count > 2)
		ft_printf("cd: string not in pwd: -\n"); // add error 1
	else if (ft_strlen(cmd->full_cmd[1]) != 1)
		ft_printf("cd: no such file or directory: %s\n", cmd->full_cmd[1]); // add error 1
	else
		change_path(ht_search("OLDPWD"));
}
void	cd_path(char *root_path, t_link_cmds *cmd, char *symbol)
{
	char	*path;

	if (cmd->count == 1 || ft_strlen(cmd->full_cmd[1]) == 1)
		change_path(ht_search(root_path));
	else
	{
		path = ft_strappend(ht_search(root_path), ft_strtrim(cmd->full_cmd[1], symbol), FALSE);
		change_path(path);
	}
}

void	cd(t_link_cmds *cmd)
{
	if (cmd->count == 1)
		change_path(ht_search("HOME"));
	else if (cmd->full_cmd[1] && ft_strncmp(cmd->full_cmd[1], "~", 1) == 0)
		cd_path("HOME", cmd, "~");
	else if (cmd->full_cmd[1] && ft_strncmp(cmd->full_cmd[1], "-", 1) == 0)
		change_to_old_path(cmd);
	else if (cmd->full_cmd[1] && ft_strncmp(cmd->full_cmd[1], ".", 1) == 0)
		cd_path("PWD", cmd, ".");
	else if (cmd->count == 3)
		ft_printf("cd: no such file or directory: %s%s\n", cmd->full_cmd[2], cmd->full_cmd[1]); //1
	else if (cmd->count > 3)
		ft_printf("cd: too many arguments"); //1
	else
		change_path(cmd->full_cmd[1]);
}
