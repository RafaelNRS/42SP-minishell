/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/14 18:44:55 by mariana          ###   ########.fr       */
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
		{
			// ft_free_array(paths);
			return (path);
		}
		free(path);
	}
	// ft_free_array(paths);
	return (NULL);
}

void	exec_cmd(t_link_cmds	*cmd, char *envp[], int *pipe_arr, bool pipe_flag)
{
	char	*path;
	int		pid;
	int		status;

	pid = fork();
	if (pipe_flag)
	{
		if (pid == 0)
		{
			dup2(pipe_arr[1], STDOUT_FILENO);
			close(pipe_arr[0]);
			close(pipe_arr[1]);
			path = ft_get_path(cmd->cmd, envp);
			if (!path)
			{
				// ft_free_array(array_cmd);
				write(2, "command not found: ", 19);
				// write(2, cmd, ft_strlen(cmd));
				// write(2, "\n", 1);
				// exit(1);
			}
			execve(path, cmd->full_cmd, envp);
		}
		waitpid(pid, &status, 0);
		dup2(pipe_arr[0], STDIN_FILENO);
		close(pipe_arr[0]);
		close(pipe_arr[1]);
	}
	else
	{
		if (pid == 0)
		{
			path = ft_get_path(cmd->cmd, envp);
			if (!path)
			{
				write(2, "command not found: ", 19);
			}
			execve(path, cmd->full_cmd, envp);
		}
		waitpid(pid, &status, 0);
	}
	// if (WIFEXITED(status)) error_status = WEXITSTATUS(status);
}

void	execute(t_link_cmds	*cmd, char *envp[], int *pipe_arr, bool pipe_flag)
{
	if (cmd->type == STRING)
	{
		if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
			export(cmd);
		else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
			unset(cmd);
		else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
			env();
		else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
			pwd(cmd);
		// else if (ft_strncmp(cmd->cmd "exit\0", 5) == 0)
		// 	exit_minishell();
		else if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
			echo(cmd);
		// else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		// 	cd(cmd);
		else
			exec_cmd(cmd, envp, pipe_arr, pipe_flag);
	}

		// achar comando, validar se tem acesso, p executar
		// static int		check_bins(char **command)
		// {
		// 	int				i;
		// 	char			*bin_path;
		// 	char			**path;
		// 	struct stat		f;

		// 	path = ft_strsplit(get_env_var("PATH"), ':');
		// 	i = -1;
		// 	while (path && path[++i])
		// 	{
		// 		if (ft_strstartswith(command[0], path[i]))
		// 			bin_path = ft_strdup(command[0]);
		// 		else
		// 			bin_path = ft_pathjoin(path[i], command[0]);
		// 		if (lstat(bin_path, &f) == -1)
		// 			free(bin_path);
		// 		else
		// 		{
		// 			ft_freestrarr(path);
		// 			return (is_executable(bin_path, f, command));
		// 		}
		// 	}
		// 	ft_freestrarr(path);
		// 	return (0);
		// }
// Search and launch the right executable (based on the PATH variable 
// or using a relative or an absolute path).

// ◦ << should be given a delimiter, then read the input until a line containing the
// delimiter is seen. However, it doesn’t have to update the history!

}