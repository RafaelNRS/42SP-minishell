/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/06/08 13:16:53 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *cmd)
{
	ft_printf("%d", cmd);
	// if (ft_strncmp(cmd, "export\0", 7) == 0)
	// 	export(cmd);
	// if (ft_strncmp(cmd, "unset\0", 6) == 0)
	// 	unset(cmd);
	// if (ft_strncmp(cmd, "env\0", 4) == 0)
	// 	env();
	// if (ft_strncmp(cmd, "pwd\0", 4) == 0)
	// 	pwd(cmd);
	// if (ft_strncmp(cmd, "exit\0", 5) == 0)
	// 	exit_minishell();
	// if (ft_strncmp(cmd, "echo\0", 5) == 0)
	// 	echo(cmd);
	// if (ft_strncmp(cmd, "cd\0", 3) == 0)
	// 	cd(cmd);
		// else
		// 	exec_cmd(cmd);
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
			// Search and launch the right executable (based on the PATH variable or using a
// relative or an absolute path).
// < should redirect input.
// ◦ > should redirect output.
// ◦ << should be given a delimiter, then read the input until a line containing the
// delimiter is seen. However, it doesn’t have to update the history!
// ◦ >> should redirect output in append mode.
// $ var

}

// void	ft_close_fd(int *fd)
// {
// 	close(fd[0]);
// 	close(fd[1]);
// }


// void set_input_file(char *file_name, int *fd)
// {
// 	char	*complete_path;
// 	int		infile;

// 	if (file_name)
// 	{
// 		// igual output refactor
// 		complete_path = get_complet_path(file_name);
// 		infile = open(complete_path, O_RDONLY);
// 		if (errno != 0)
// 		{
// 			ft_close_fd(fd);
// 			if (errno != 0)
// 			{
// 				ft_printf("deu erro no input");
// 				// ft_check_error(file);
// 			}
// 		}
// 		free(complete_path);
// 		dup2(infile, STDIN_FILENO);
// 		close(infile);
// 	}
// }

// void	set_input()
// {
// 	dup2(fd[0], STDIN_FILENO);
// }

// void set_output_file
// {
// 	char	*complete_path;
// 	int		outfile;

// 	if (file_name)
// 	{
// 		complete_path = get_complet_path(file_name);
// 		outfile = open(complete_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (errno != 0)
// 		{
// 			ft_close_fd(fd);
// 			if (errno != 0)
// 			{
// 				ft_printf("deu erro no input");
// 				// ft_check_error(file);
// 			}
// 		}
// 		free(complete_path);
// 		dup2(outfile, STDOUT_FILENO);
// 		close(outfile);
// 	}
// }


// void	execute(TokenList *cmd)
// {	
// 	int		fd[2];
// 	int		pid;

// 	if (pipe(fd) == -1)
// 		ft_printf("Error: Pipe\n");
// 	cmd_list[0] = [cat] [bolinha]
// 	cmd_list[1] = [grep] [o]

// 	while (cmd_list)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			ft_printf("Error: Fork\n");
// 		if (pid == 0)
// 		{
// 			if (cmd_list->next && is_output(cmd_list->next))
// 				set_output_file(cmd_list->next)
// 			else if (cmd_list->next)
// 				set_output;
// 			else
// 				reset_out;

// 			if (cmd_list->next)
// 			{
// 				if (is_input())
// 					set_input_file();
// 				else
// 				{
// 					if (not_the_first)
// 						set_input;
// 					execute_commands(cmd);
// 				}
// 			}
// 			else
// 			{
// 				if (!is_output(cmd_list))
// 					execute_commands(cmd);
// 			}
// 		}
// 		reset_in_out;
// 		ft_close_fd(fd);
// 		waitpid(pid, NULL, 0);
// 		free(cmd_list);
// 	}
// }
