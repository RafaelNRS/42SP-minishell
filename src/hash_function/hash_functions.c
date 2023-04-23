/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:07:58 by mariana           #+#    #+#             */
/*   Updated: 2023/04/23 13:46:36 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	*create_table(int size)
{
	t_table	*new_table;
	int		i;

	new_table = (t_table *)ft_calloc(sizeof(t_table), 1);
	new_table->size = size;
	new_table->count = 0;
	new_table->bucket_items = (t_item **)ft_calloc(sizeof(t_table), size);
	i = 0;
	while (i < size)
	{
		new_table->bucket_items[i] = NULL;
		i++;
	}
	return (new_table);
}

int	hash_function(char *key, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (key[j++])
		i += key[j];
	return (i % size);
}
