/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:15:01 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_piped_command(t_link_cmds *current_cmd)
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

static int	redirect_out(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	fd_open = open(next_cmd->full_cmd[0], flags, 0777);
	if (fd_open == -1)
	{
		msh_error(1, "minishell", "Permission denied.");
		return 0;
	}
	else
	{
		dup2(fd_open, OUT);
		close(fd_open);
		return 1;
	}
}

static int	redirect_in(t_link_cmds *next_cmd, int flags)
{
	int	fd_open;

	if (access(next_cmd->full_cmd[0], F_OK) == -1)
	{
		msh_error(1, "minishell", "No such file or directory.");
		return 0;
	}
	fd_open = open(next_cmd->full_cmd[0], flags);
	if (fd_open == -1)
	{
		msh_error(1, "minishell", "Permission denied.");
		return 0;
	}
	else
	{
		dup2(fd_open, IN);
		close(fd_open);
		return 1;
	}
}

void	heredoc_signal(int signal)
{
	(void)signal;
	g_msh.error_code = 130;
	write(2, "\n", 1);
	exit(130);
}

static void	receive_input(int tmp_file, char *eof)
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

static void	read_tmp_file(void)
{
	int	tmp_file;

	tmp_file = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_file, IN);
	close(tmp_file);
}

static void	heredoc(char *eof, int *fd)
{
	int	tmp_file;
	int	save_out;
	int	pid;
	int	status;

	fd[0] = 0;
	fd[1] = 0;
	tmp_file = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_file == -1)
		return ;
	save_out = dup(OUT);
	dup2(fd[OUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		receive_input(tmp_file, eof);
	waitpid(pid, &status, 0);
	read_tmp_file();
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
}

static int	check_redirections(t_link_cmds *nc, int *fd)
{
	int		changed;
	t_link_cmds	*current_cmd;

	current_cmd = nc;
	changed = 0;
	while (nc && (nc->type >= FILE && nc->type <= END_OF_FILE))
	{
		if (nc->type == END_OF_FILE)
			heredoc(nc->full_cmd[0], fd);
		nc = nc->next;
	}
	nc = current_cmd;
	while (nc && (nc->type >= FILE && nc->type <= END_OF_FILE))
	{
		if (nc->type == INPUT_FILE && !redirect_in(nc, O_RDONLY))
				return -1;
		nc = nc->next;
	}
	nc = current_cmd;
	while (nc && (nc->type >= FILE && nc->type <= END_OF_FILE))
	{
		if (nc->type == FILE)
			changed = redirect_out(nc, O_WRONLY | O_CREAT | O_TRUNC);
		else if (nc->type == FILE_A)
			changed = redirect_out(nc, O_WRONLY | O_CREAT | O_APPEND);
		nc = nc->next;
	}
	return (changed);
}

void	execute_cmds(t_link_cmds *chained_cmds)
{
	t_link_cmds	*current_cmd;
	int			fd[2];
	int			saved_stdin;
	int			saved_stdout;
	int			changed;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	current_cmd = chained_cmds;
	changed = 0;
	while (current_cmd && has_piped_command(current_cmd->next) \
		&& current_cmd->type == STRING)
	{
		pipe(fd);
		changed = check_redirections(current_cmd->next, fd);
		if (changed != -1)
			execute(current_cmd, fd, TRUE);
		else
			break;
		if (changed == 1)
			dup2(saved_stdout, STDOUT_FILENO);
		current_cmd = current_cmd->next;
		while (current_cmd && current_cmd->type >= FILE && current_cmd->type <= END_OF_FILE)
			current_cmd = current_cmd->next;
	}
	if (check_redirections(current_cmd->next, fd) != -1)
		execute(current_cmd, fd, FALSE);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	while (current_cmd->next && current_cmd->next->type >= FILE && current_cmd->next->type <= END_OF_FILE)
		current_cmd = current_cmd->next;
	if (current_cmd->next && current_cmd->next->type == SEMICOLON \
		&& current_cmd->next->next)
		execute_cmds(current_cmd->next->next);
}

int	syntax_analysis(t_token_list *tokens_lst)
{
	t_link_cmds	*chained_cmds;
	t_link_cmds *first_node;

	validate_tokens(tokens_lst);
	chained_cmds = create_cmds(tokens_lst);
	cleanup_token_list(tokens_lst);
	first_node = chained_cmds;
	execute_cmds(chained_cmds);
	if (first_node)
		cleanup_chained_cmd(first_node);
	return (0);
}
