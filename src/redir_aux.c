/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:32:38 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:33:28 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir_out(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	set_redir_in(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}
