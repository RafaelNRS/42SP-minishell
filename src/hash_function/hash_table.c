/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:17:03 by mariana           #+#    #+#             */
/*   Updated: 2023/04/23 13:24:35 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

h_table	*alloc_hash_table(char **env)
{
	int		i;
	int		size;
	h_table	*table;

	size = 0;
	while (env[size])
		size++;
	table = create_table(size * 2);
	i = 0;
	while (env[i])
	{
		add_h_item(env[i], table);
		i++;
	}
	return (table);
}

char	*ht_search(h_table *table, char *key)
{
	int		index;
	h_item	*current;

	index = hash_function(key, table->size);
	current = table->bucket_items[index];
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->value);
		else
			current = current->next;
	}
	if (!current)
	{
		write(2, "command not found ", 18);
		write(2, key, ft_strlen(key));
		write(2, "\n", 1);
	}
	return (NULL);
}

void	print_table(h_table *hash_env)
{
	int		i;
	int		j;
	h_item	*current;

	i = 0;
	j = 0;
	while (i < hash_env->count)
	{
		current = hash_env->bucket_items[j];
		while (current)
		{
			write(2, current->key, ft_strlen(current->key));
			write(2, "=", 1);
			write(2, current-> value, ft_strlen(current-> value));
			write(2, "\n", 1);
			i++;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		j++;
	}
}
