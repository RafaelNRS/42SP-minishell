/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:02:35 by mariana           #+#    #+#             */
/*   Updated: 2023/05/20 11:26:43 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_tk_lst *var)
{
	int	i;

	i = 1;
	while (i < var->count)
	{
		delete_item(var->tokens[i]);
		i++;
	}
}
