/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:16:39 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:26:20 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	can_execute(char *path)
{
	struct stat	s_buffer;

	if (!access(path, F_OK) && !stat(path, &s_buffer) \
		&& ((s_buffer.st_mode & S_IFMT) != S_IFDIR) \
		&& ((s_buffer.st_mode & S_IXUSR)))
		return (TRUE);
	return (FALSE);
}

char	*ft_get_path(char *cmd)
{
	char		**paths;
	int			i;
	char		*path;
	char		*partial_path;

	paths = ft_split(ht_search("PATH"), ':');
	i = 0;
	while (paths[i++])
	{
		partial_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (can_execute(path))
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

void	interrupt_signal(int signal)
{
	(void)signal;
	g_msh.error_code = 130;
	write(2, "\n", 1);
}

void	quit_signal(int signal)
{
	(void)signal;
	g_msh.error_code = 131;
	write(2, "\n", 1);
}
