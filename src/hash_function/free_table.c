/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:15:28 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 13:03:36 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_item(t_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	free_hash_table(void)
{
	int		i;
	t_item	*current;
	t_item	*temp;

	i = 0;
	while (i < g_msh.env->size)
	{
		current = g_msh.env->bucket_items[i];
		while (current != NULL)
		{
			temp = current->next;
			free_item(current);
			current = temp;
		}
		i++;
	}
	free(g_msh.env->bucket_items);
	free(g_msh.env);
}
