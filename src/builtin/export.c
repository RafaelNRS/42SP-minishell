/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:01:54 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 12:29:00 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(TokenList *var)
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
