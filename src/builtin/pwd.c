/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:03:45 by mariana           #+#    #+#             */
/*   Updated: 2023/05/22 17:00:00 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_token_list *cmd)
{
	if (cmd->count > 1)
		ft_printf("pwd: too many arguments\n");
	else
		ft_printf("%s\n", ht_search("PWD"));
}
