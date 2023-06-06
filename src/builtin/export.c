/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:01:54 by mariana           #+#    #+#             */
/*   Updated: 2023/05/22 17:00:00 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_token_list *var)
{
	t_token *current;

	current = var->head->next;
	if (var->count == 2)
	{
		if (ft_strchr(current->token, '='))
			add_t_item(current->token);
	}
	else
	{
		while (current != NULL)
		{
			if (ft_strchr(current->token, '='))
				add_t_item(current->token);
			current = current->next;
		}
	}
}
