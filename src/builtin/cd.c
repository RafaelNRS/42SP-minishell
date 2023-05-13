/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:22:23 by mariana           #+#    #+#             */
/*   Updated: 2023/05/13 12:18:40 by mariana          ###   ########.fr       */
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

void	change_to_old_path(TokenList *cmd)
{
	if (ft_strlen(cmd->tokens[1]) != 1)
		ft_printf("cd: %s: invalid option\n", cmd->tokens[1]);
	else
		change_path(ht_search("OLDPWD"));
}

void	cd_path(char *root_path, TokenList *cmd)
{
	char	*tmp_path;
	char	*path;
	int		len;
	int		root_len;

	if (cmd->count == 1 || ft_strlen(cmd->tokens[1]) == 1)
		change_path(ht_search(root_path));
	else
	{
		path = (char *)(cmd->tokens[1] + 1);
		root_len = ft_strlen(ht_search(root_path));
		len = root_len + ft_strlen(path) + 1;
		tmp_path = (char *) malloc(sizeof(char) * len);
		ft_strlcpy(tmp_path, ht_search(root_path), root_len + 1);
		ft_strlcat(tmp_path, path, len);
		change_path(tmp_path);
		free(tmp_path);
	}
}

void	cd(TokenList *cmd)
{
	if (cmd->count > 2)
		ft_printf("cd: too many arguments\n");
	if (cmd->count == 1)
		change_path(ht_search("HOME"));
	else if (ft_strncmp(cmd->tokens[1], "~", 1) == 0)
		cd_path("HOME", cmd);
	else if (ft_strncmp(cmd->tokens[1], "-", 1) == 0)
		change_to_old_path(cmd);
	else if (ft_strncmp(cmd->tokens[1], ".", 1) == 0)
		cd_path("PWD", cmd);
	else
		change_path(cmd->tokens[1]);
}
