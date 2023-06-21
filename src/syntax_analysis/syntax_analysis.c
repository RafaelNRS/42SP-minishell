/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/21 12:21:24 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_piped_command(t_link_cmds *current_cmd)
{
	while (current_cmd)
	{
		if (current_cmd->type == SEMICOLON)
			return FALSE;
		if (current_cmd->type == STRING)
			return TRUE;
		current_cmd = current_cmd->next;
	}
	return FALSE;
}

static void	redirect_out(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	fd_open = open(next_cmd->full_cmd[0], flags, 0777);
	if (fd_open == -1)
		msh_error(1);
	else
	{
		dup2(fd_open, OUT);
		close(fd_open);
	}
}

static void	redirect_in(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	fd_open = open(next_cmd->full_cmd[0], flags);
	if (fd_open == -1)
		msh_error(1);
	else
	{
		dup2(fd_open, IN);
		close(fd_open);
	}
}

static void	heredoc(char *eof, int *fd)
{
	
}

static bool	check_redirections(t_link_cmds *next_cmd, int *fd)
{
	bool	changed;

	changed = FALSE;
	while (next_cmd && (next_cmd->type >= FILE && \
				next_cmd->type <= END_OF_FILE) )
	{
		if (next_cmd->type == FILE)
			redirect_out(next_cmd, O_WRONLY | O_CREAT | O_TRUNC);
		else if (next_cmd->type == FILE_A)
			redirect_out(next_cmd, O_WRONLY | O_CREAT | O_APPEND);
		else if (next_cmd->type == INPUT_FILE)
			redirect_in(next_cmd, O_RDONLY | O_CREAT);
		else if (next_cmd->type == END_OF_FILE)
			printf("TODO: heredoc(next_cmd->full_cmd[0], fd); - %d\n",fd[0]);
		
		changed = TRUE;
		next_cmd = next_cmd->next;
	}
	return (changed);
}

void	execute_cmds(t_link_cmds *chained_cmds, char *envp[])
{
	t_link_cmds	*current_cmd;
	int			fd[2];
	int			saved_stdin;
	int			saved_stdout;
	bool		changed;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	current_cmd = chained_cmds;
	while (current_cmd && has_piped_command(current_cmd->next) \
		&& current_cmd->type == STRING)
	{
		pipe(fd);
		changed = check_redirections(current_cmd->next, fd);
		execute(current_cmd, envp, fd, TRUE);
		current_cmd = current_cmd->next;
		while (current_cmd && current_cmd->type >= FILE && current_cmd->type <= END_OF_FILE)
			current_cmd = current_cmd->next;
	}
	if (changed)
		dup2(saved_stdout, STDOUT_FILENO);
	check_redirections(current_cmd->next, fd);
	execute(current_cmd, envp, fd, FALSE);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	while (current_cmd->next && current_cmd->next->type >= FILE && current_cmd->next->type <= END_OF_FILE)
		current_cmd = current_cmd->next;
	if (current_cmd->next && current_cmd->next->type == SEMICOLON \
		&& current_cmd->next->next)
			execute_cmds(current_cmd->next->next, envp);
}

int	syntax_analysis(t_token_list *tokens_lst, char *envp[])
{
	t_link_cmds	*chained_cmds;

	validate_tokens(tokens_lst);
	chained_cmds = create_cmds(tokens_lst);
	execute_cmds(chained_cmds, envp);
	return (0);
}
