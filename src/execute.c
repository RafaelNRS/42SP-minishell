/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/20 16:36:20 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_var_path(char *envp[])
{
	int	i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

char	*ft_get_path(char *cmd, char *envp[])
{
	char	**paths;
	int		i;
	char	*path;
	char	*partial_path;

	paths = ft_get_var_path(envp);
	i = 0;
	while (paths[++i])
	{
		partial_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (!access(path, F_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

void	exec_func(t_link_cmds	*cmd, char *envp[])
{
	char	*path;

	path = ft_get_path(cmd->full_cmd[0], envp);
	if (!path)
		fprintf(stderr, "command not found: %s\n", cmd->full_cmd[0]);
		//write(2, "command not found: \n", 20);
		
	execve(path, cmd->full_cmd, envp);
}

void	exec_cmd(t_link_cmds	*cmd, char *envp[])
{
	if (ft_strncmp(cmd->full_cmd[0], "export\0", 7) == 0)
		export(cmd);
	else if (ft_strncmp(cmd->full_cmd[0], "unset\0", 6) == 0)
		unset(cmd);
	else if (ft_strncmp(cmd->full_cmd[0], "env\0", 4) == 0)
		env();
	else if (ft_strncmp(cmd->full_cmd[0], "pwd\0", 4) == 0)
		pwd(cmd);
	// else if (ft_strncmp(cmd->full_cmd[0], "exit\0", 5) == 0)
	// 	exit_minishell();
	// else if (ft_strncmp(cmd->full_cmd[0], "cd\0", 3) == 0)
	// 	cd();
	else if (ft_strncmp(cmd->full_cmd[0], "echo\0", 5) == 0)
		echo(cmd);
	else
		exec_func(cmd, envp);
}

void	execute(t_link_cmds	*cmd, char *envp[], int *fd, bool flag)
{
	int pid;
    int status;

	// TODO refactor too big
	pid = fork();
	if (flag)
	{
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec_cmd(cmd, envp);
			exit(1);
		}
		waitpid(pid, &status, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (pid == 0)
		{
			exec_cmd(cmd, envp);
			exit(1);
		}
		waitpid(pid, &status, 0);
	}
}
