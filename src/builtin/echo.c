/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:09:25 by mariana           #+#    #+#             */
/*   Updated: 2023/05/22 17:00:00 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token_list *cmd)
{
	int	has_flag_n;
	t_token *current;

	current = cmd->head->next;
	if (cmd->count > 1)
	{
		has_flag_n = 0;
		if (ft_strncmp(current->token, "-n", 2) == 0
			&& ft_strlen(current->token) == 2)
		{
			has_flag_n++;
			current = current->next;
		}
		while (current != NULL)
		{
			if (current->next == NULL && has_flag_n)
				ft_printf("%s", current->token);
			else if (current->next == NULL)
				ft_printf("%s\n", current->token);
			else
				ft_printf("%s ", current->token);
			current = current->next;
		}
	}
}
