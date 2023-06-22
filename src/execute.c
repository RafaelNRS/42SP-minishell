/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/22 00:25:52 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *cmd)
{
	char	**paths;
	int		i;
	char	*path;
	char	*partial_path;

	paths = ft_split(ht_search("PATH"), ':');
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

char	**env_list(void)
{
	int		i;
	int		j;
	t_item	*current;
	char	**env_list;

	i = 0;
	j = 0;
	env_list = (char **) malloc((g_msh.env->count + 1) * sizeof(char *));
	while (i < g_msh.env->count)
	{
		current = g_msh.env->bucket_items[j];
		while (current)
		{
			env_list[i] = join_n_strs(3, current->key, "=", current-> value);
			i++;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		j++;
	}
	env_list[i] = NULL;
	return (env_list);
}

void	exec_func(t_link_cmds	*cmd)
{
	char	*path;
	char	**list;

	path = ft_get_path(cmd->full_cmd[0]);
	if (!path)
		write(2, "command not found: ", 19);
	list = env_list();
	execve(path, cmd->full_cmd, list);
}

void	exec_cmd(t_link_cmds	*cmd,int *fd, bool flag)
{
	int	pid;
	int	status;

	// TODO refactor too big
	pid = fork();
	if (flag)
	{
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec_func(cmd);
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
			exec_func(cmd);
			exit(1);
		}
		waitpid(pid, &status, 0);
	}

}

void	execute(t_link_cmds	*cmd, int *fd, bool flag)
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
		exec_cmd(cmd, fd, flag);
}
