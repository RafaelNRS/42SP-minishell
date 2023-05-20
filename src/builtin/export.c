/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:01:54 by mariana           #+#    #+#             */
/*   Updated: 2023/05/20 11:26:43 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_tk_lst *var)
{
	int	i;

	i = 1;
	if (var->count == 2)
	{
		if (ft_strchr(var->tokens[i], '='))
			add_t_item(var->tokens[i]);
	}
	else
	{
		while (i <= var->count)
		{
			if (ft_strchr(var->tokens[i], '='))
				add_t_item(var->tokens[i]);
			i++;
		}
	}
}
