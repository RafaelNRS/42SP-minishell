/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:03:45 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 12:39:15 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(TokenList *cmd)
{
	if (cmd->count > 1)
		ft_printf("pwd: too many arguments\n");
	else
		ft_printf("%s\n", ht_search("PWD"));
}
