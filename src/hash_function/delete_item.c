/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_item.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:23:37 by mariana           #+#    #+#             */
/*   Updated: 2023/04/23 13:46:36 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_and_delete(t_item	*current, char *key, t_table *table)
{
	t_item	*tmp_item;

	while (current->next)
	{
		if (ft_strncmp(current->next->key, key, ft_strlen(key) + 1) == 0)
		{
			tmp_item = current->next;
			current->next = current->next->next;
			free_item(tmp_item);
			table->count--;
			return ;
		}
		current = current->next;
	}
}

void	delete_item(t_table *table, char *key)
{
	int		index;
	t_item	*current;

	index = hash_function(key, table->size);
	current = table->bucket_items[index];
	if (!current)
		return ;
	if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		if (current->next)
			table->bucket_items[index] = current->next;
		else
			table->bucket_items[index] = NULL;
		free_item(current);
		table->count--;
		return ;
	}
	else
		find_and_delete(current, key, table);
}
