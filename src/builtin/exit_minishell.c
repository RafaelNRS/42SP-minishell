/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:57:55 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 12:41:21 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell()
{
	// se mandar mais argumentos
	// syntax error near unexpected token `2' -> exit(2) senao funfa normal
	// free(cmd);
	// free_hash_table();
	// if (cmd_line)
	// 	free(cmd_line);
	exit(1);
}
