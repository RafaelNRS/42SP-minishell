/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 20:32:53 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_func(t_link_cmds	*cmd)
{
	char	*path;
	char	**list;

	if (!ft_strrchr(cmd->full_cmd[0], '.') && \
		!ft_strrchr(cmd->full_cmd[0], '/'))
		path = ft_get_path(cmd->full_cmd[0]);
	else
	{
		path = cmd->full_cmd[0];
		if (access(path, F_OK))
			write(2, "no such file or directory.\n", 28);
		else if (!can_execute(path))
			write(2, "Permission denied.\n", 20);
	}
	if (!path)
		write(2, "command not found.\n", 20);
	list = env_list();
	execve(path, cmd->full_cmd, list);
}

void	exec_cmd(t_link_cmds *cmd)
{
	if (ft_strncmp(cmd->full_cmd[0], "env\0", 4) == 0)
		env();
	else if (ft_strncmp(cmd->full_cmd[0], "pwd\0", 4) == 0)
		pwd();
	else if (ft_strncmp(cmd->full_cmd[0], "echo\0", 5) == 0)
		echo(cmd, FALSE, 1);
	else
		exec_func(cmd);
	exit(1);
}

static void	exec_external(t_link_cmds *cmd, int *fd, bool flag)
{
	int	pid;
	int	status;

	pid = fork();
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, quit_signal);
	if (flag)
	{
		if (pid == 0)
		{
			set_redir_out(fd);
			exec_cmd(cmd);
		}
		waitpid(pid, &status, 0);
		set_redir_in(fd);
	}
	else
	{
		if (pid == 0)
			exec_cmd(cmd);
		waitpid(pid, &status, 0);
	}
	g_msh.error_code = status;
}

void	execute(t_link_cmds	*cmd, int *fd, bool flag, int exec_flag)
{	
	if (exec_flag == -1)
		return ;
	if (ft_strncmp(cmd->full_cmd[0], "export\0", 7) == 0)
		export(cmd);
	else if (ft_strncmp(cmd->full_cmd[0], "unset\0", 6) == 0)
		unset(cmd);
	else if (ft_strncmp(cmd->full_cmd[0], "cd\0", 3) == 0)
		cd(cmd);
	else if (ft_strncmp(cmd->full_cmd[0], "exit\0", 5) == 0)
		msh_exit(cmd);
	else
		exec_external(cmd, fd, flag);
}
