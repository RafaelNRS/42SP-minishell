/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/19 18:51:50 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmds(t_link_cmds *chained_cmds)
{
	t_link_cmds	*current_cmd;
	int			fd[2];
	int			saved_stdin;

	current_cmd = chained_cmds;
	saved_stdin = dup(STDIN_FILENO);
	while (current_cmd && current_cmd->next)
	{
		pipe(fd);
		execute(current_cmd, fd, TRUE);
		current_cmd = current_cmd->next;
	}
	execute(current_cmd, fd, FALSE);
	dup2(saved_stdin, STDIN_FILENO);
}

int	syntax_analysis(t_token_list *tokens_lst)
{
	t_link_cmds	*chained_cmds;

	validate_tokens(tokens_lst);
	chained_cmds = create_cmds(tokens_lst);
	execute_cmds(chained_cmds);
	return (0);
}
