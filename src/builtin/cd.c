/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:22:23 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 13:03:57 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_path(char *path)
{
	DIR		*dir;
	char	*old_path;
	char	*pwd;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		old_path = ft_strjoin("OLDPWD=", ht_search("PWD"));
		pwd = ft_strjoin("PWD=", path);
		add_t_item(old_path);
		add_t_item(pwd);
		free(old_path);
		free(pwd);
	}
	else if (ENOENT == errno)
		ft_printf("cd: no such file or directory: %s", path);
	else
		ft_printf("cd: %s", errno);
}

void	cd_home(void)
{
	char	*old_path;
	char	*pwd;

	old_path = ft_strjoin("OLDPATH=", ht_search("PWD"));
	pwd = ft_strjoin("PWD=", ht_search("HOME"));
	add_t_item(old_path);
	add_t_item(pwd);
	free(old_path);
	free(pwd);
}

void	cd_tilde(TokenList *cmd)
{
	char	*tmp_path;

	if (cmd->count >= 3)
		ft_printf("cd: too many arguments");
	if (cmd->count == 1 || ft_strlen(cmd->tokens[1]) == 1)
		cd_home();
	else
	{
		tmp_path = ft_strjoin(ht_search("HOME"), cmd->tokens[1]);
		change_path(tmp_path);
		free(tmp_path);
	}
}

void	change_to_old_path(TokenList *cmd)
{
	if (cmd->count > 2)
		ft_printf("cd: too many arguments\n");
	else if (ft_strlen(cmd->tokens[1]) != 1)
		ft_printf("cd: %s: invalid option\n", cmd->tokens[1]);
	else
		change_path(cmd->tokens[1]);
}

void	cd(TokenList *cmd)
{
	if (cmd->count == 1)
		cd_home();
	if (ft_strncmp(cmd->tokens[1], "~", 1))
		cd_tilde(cmd);
	if (ft_strncmp(cmd->tokens[1], "-", 1))
		change_to_old_path(cmd);
	else
	{
		if (cmd->count != 2)
			ft_printf("cd: too many arguments");
		else
			change_path(cmd->tokens[1]);
	}
}
