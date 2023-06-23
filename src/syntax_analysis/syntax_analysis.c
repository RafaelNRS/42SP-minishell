/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 20:20:29 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			changed;
	t_link_cmds	*current_cmd;

	current_cmd = nc;
	changed = 0;
	while (nc && (nc->type >= FILE && nc->type <= END_OF_FILE))
	{
		if (nc->type == END_OF_FILE)
			heredoc(nc->full_cmd[0], fd);
		if (nc->type == INPUT_FILE && !redirect_in(nc, O_RDONLY))
			return (-1);
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

static void	execute_cmds(t_link_cmds *chain, int o_in, int o_out, int chg)
{
	t_link_cmds	*c_c;
	int			fd[2];

	c_c = chain;
	while (c_c && has_piped_command(c_c->next) && c_c->type == STRING)
	{
		pipe(fd);
		chg = check_redirections(c_c->next, fd);
		if (chg == -1)
			break ;
		execute(c_c, fd, TRUE, chg);
		if (chg == 1)
			dup2(o_out, STDOUT_FILENO);
		c_c = c_c->next;
		while (c_c && c_c->type >= FILE && c_c->type <= END_OF_FILE)
			c_c = c_c->next;
	}
	execute(c_c, fd, FALSE, check_redirections(c_c->next, fd));
	dup2(o_in, STDIN_FILENO);
	dup2(o_out, STDOUT_FILENO);
	while (c_c->next && c_c->next->type >= FILE && \
		c_c->next->type <= END_OF_FILE)
		c_c = c_c->next;
	if (c_c->next && c_c->next->type == SEMICOLON && c_c->next->next)
		execute_cmds(c_c->next->next, dup(STDIN_FILENO), dup(STDOUT_FILENO), 0);
}

int	syntax_analysis(t_token_list *tokens_lst)
{
	t_link_cmds	*chained_cmds;
	t_link_cmds	*first_node;
	t_link_cmds	*cmds;

	validate_tokens(tokens_lst);
	cmds = create_chained_cmd();
	chained_cmds = create_cmds(cmds, 0, \
		tokens_lst->head, tokens_lst->head->type);
	cleanup_token_list(tokens_lst);
	first_node = chained_cmds;
	execute_cmds(chained_cmds, dup(STDIN_FILENO), dup(STDOUT_FILENO), 0);
	if (first_node)
		cleanup_chained_cmd(first_node);
	return (0);
}
