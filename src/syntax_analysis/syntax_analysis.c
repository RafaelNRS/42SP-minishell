/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/19 22:22:53 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_piped_command(t_link_cmds *current_cmd)
{
	while (current_cmd)
	{
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

// static void	heredoc(t_link_cmds *next_cmd, int *fd)
// {
	
// }

static void	check_redirections(t_link_cmds *next_cmd, int *fd)
{
	if (!next_cmd || (next_cmd->type < FILE && \
				next_cmd->type > END_OF_FILE) )
		return ;
	if (next_cmd->type == FILE)
		redirect_out(next_cmd, O_WRONLY | O_CREAT | O_TRUNC);
	else if (next_cmd->type == FILE_A)
		redirect_out(next_cmd, O_WRONLY | O_CREAT | O_APPEND);
	else if (next_cmd->type == INPUT_FILE)
		redirect_in(next_cmd, O_RDONLY | O_CREAT);
	else if (next_cmd->type == END_OF_FILE)
		printf("TODO: heredoc(next_cmd, fd); - %d\n",fd[0]);
}

void	execute_cmds(t_link_cmds *chained_cmds, char *envp[])
{
	t_link_cmds	*current_cmd;
	int			fd[2];
	int			saved_stdin;
	int			saved_stdout;

	current_cmd = chained_cmds;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (current_cmd && has_piped_command(current_cmd->next))
	{
		pipe(fd);
		check_redirections(current_cmd->next, fd);
		execute(current_cmd, envp, fd, TRUE);
		current_cmd = current_cmd->next;
	}
	check_redirections(current_cmd->next, fd);
	execute(current_cmd, envp, fd, FALSE);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
}

int	syntax_analysis(t_token_list *tokens_lst, char *envp[])
{
	t_link_cmds	*chained_cmds;

	validate_tokens(tokens_lst);
	chained_cmds = create_cmds(tokens_lst);
	execute_cmds(chained_cmds, envp);
	return (0);
}
