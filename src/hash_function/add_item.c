/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:24:41 by mariana           #+#    #+#             */
/*   Updated: 2023/04/23 13:39:05 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_key(const char *s, int c)
{
	char	*p;
	int		i;
	int		z;

	i = 0;
	while (s[i] != c)
		i++;
	p = (char *) malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	z = 0;
	while (z < i)
	{
		p[z] = s[z];
		z++;
	}
	p[z] = '\0';
	return (p);
}

h_item	*create_new_item(char *var)
{
	h_item	*new_item;
	char	*value;
	char	*key;

	new_item = (h_item *)ft_calloc(sizeof(h_item), 1);
	if (!new_item)
		msh_error(2);
	key = get_key(var, '=');
	if (key)
	{
		new_item->key = key;
		value = get_value(var, '=');
		if (value)
			new_item->value = ft_strdup(value);
		else
			new_item->value = NULL;
		new_item->next = NULL;
		return (new_item);
	}
	return (NULL);
}

void	chage_item(h_item *current, h_item *new_item, h_table *table)
{
	int		len;

	while (current)
	{
		len = ft_strlen(new_item->key) + 1;
		if (ft_strncmp(current->key, new_item->key, len) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_item->value);
			free_item(new_item);
			return ;
		}
		else
		{
			if (current->next)
				current = current->next;
			else
			{
				current->next = new_item;
				table->count++;
				break ;
			}
		}
	}
}

// unsigned long int
void	add_h_item(char *var, h_table *table)
{
	h_item	*new_item;
	h_item	*current;
	int		hash_index;

	if (table->count == table->size)
		msh_error(3);
	new_item = create_new_item(var);
	hash_index = hash_function(new_item->key, table->size);
	current = table->bucket_items[hash_index];
	if (!current)
	{
		table->bucket_items[hash_index] = new_item;
		table->count++;
	}
	else
		chage_item(current, new_item, table);
}
