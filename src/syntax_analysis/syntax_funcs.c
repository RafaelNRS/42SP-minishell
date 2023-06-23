/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:19:40 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:22:32 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_piped_command(t_link_cmds *current_cmd)
{
	while (current_cmd)
	{
		if (current_cmd->type == SEMICOLON)
			return (FALSE);
		if (current_cmd->type == STRING)
			return (TRUE);
		current_cmd = current_cmd->next;
	}
	return (FALSE);
}

int	redirect_out(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	fd_open = open(next_cmd->full_cmd[0], flags, 0777);
	if (fd_open == -1)
	{
		msh_error(1, "minishell", "Permission denied.");
		return (0);
	}
	else
	{
		dup2(fd_open, OUT);
		close(fd_open);
		return (1);
	}
}

int	redirect_in(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	if (access(next_cmd->full_cmd[0], F_OK) == -1)
	{
		msh_error(1, "minishell", "No such file or directory.");
		return (0);
	}
	fd_open = open(next_cmd->full_cmd[0], flags);
	if (fd_open == -1)
	{
		msh_error(1, "minishell", "Permission denied.");
		return (0);
	}
	else
	{
		dup2(fd_open, IN);
		close(fd_open);
		return (1);
	}
}

void	heredoc_signal(int signal)
{
	(void)signal;
	g_msh.error_code = 130;
	write(2, "\n", 1);
	exit(130);
}

void	receive_input(int tmp_file, char *eof)
{
	char	*input;

	signal(SIGINT, heredoc_signal);
	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			close(tmp_file);
			exit(0);
		}
		if (ft_strncmp(input, eof, ft_strlen(eof)))
			ft_putendl_fd(input, tmp_file);
		else
		{
			close(tmp_file);
			free(input);
			break ;
		}
		free(input);
	}
	exit (0);
}
