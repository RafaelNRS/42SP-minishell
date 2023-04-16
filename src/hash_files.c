/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:17:03 by mariana           #+#    #+#             */
/*   Updated: 2023/04/16 20:01:24 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

h_table *create_table(int size)
{
	h_table	*new_table;
	int	i;

	new_table = (h_table *)ft_calloc(sizeof(h_table), 1);
	new_table->size = size;
	new_table->count = 0;
	new_table->bucket_items = (h_item **)ft_calloc(sizeof(h_table), size);
	i = 0;
	while (i < size)
	{
		new_table->bucket_items[i] = NULL;
		i++;
	}
	return (new_table);
}

char	*get_value(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i+1]);
		i++;
	}
	return (NULL);
}

char	*get_key(const char *s, int c)
{
	char	*p;
	int	i;
	int	z;

	i = 0;
	while(s[i] != c)
		i++;
	p = (char *) malloc((i+1) * sizeof(char));
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

int	hash_function(char *key, int size)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (key[j++])
		i += key[j];

    return i % size;
}

void free_item(h_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	free_hash_table(h_table *table)
{
	int		i;
	h_item	*current;
	h_item	*temp;

	i = 0;
	while (i < table->size)
	{
		current = table->bucket_items[i];
		while (current != NULL)
		{
			temp = current->next;
			free_item(current);
			current = temp;
		}
		i++;
	}
	free(table->bucket_items);
	free(table);
}

void	add_h_item(char *var, h_table *table)
{
	h_item	*new_item;
	h_item	*current;
	int 	hash_index;
	// unsigned long int

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
	{
		while(current)
		{
			if (ft_strncmp(current->key, new_item->key, ft_strlen(new_item->key) + 1) == 0)
			{
				free(current->value);
				current->value = ft_strdup(new_item->value);
				free_item(new_item);
				return;
			}
			else
			{
				if (current->next)
					current = current->next;
				else
				{
					current->next = new_item;
					table->count++;
					break;
				}
			}
		}
	}
}

h_table *alloc_hash_table(char **env)
{
	int i;
	int size;
	h_table *table;

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

void delete_item(h_table *table, char *key)
{
	int index;
	h_item *current;
	h_item *tmp_item;

	index = hash_function(key, table->size);
	current = table->bucket_items[index];
	if (!current)
		return;
	if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		if (current->next)
			table->bucket_items[index] = current->next;
		else
			table->bucket_items[index] = NULL;
		free_item(current);
		table->count--;
		return;
	}
	else
	{
		while(current->next)
		{
			if (ft_strncmp(current->next->key, key, ft_strlen(key) + 1) == 0)
			{
				tmp_item = current->next;
				current->next = current->next->next;
				free_item(tmp_item);
				table->count--;
				return;
			}
			current = current->next;
		}
	}
}

char *ht_search(h_table *table, char *key)
{
	int index;
	h_item *current;

	index = hash_function(key, table->size);
	current = table->bucket_items[index];
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return current->value;
		else
			current = current->next;
	}
	if (!current)
	{
		write(2, "command not found ", 18);
		write(2, key, ft_strlen(key));
		write(2, "\n", 1);
	}
	return NULL;
}

void print_table(h_table *hash_env)
{
	int i;
	int j;
	h_item *current;

	i = 0;
	j= 0;
	while(i < hash_env->count)
	{
		current = hash_env->bucket_items[j];
		while (current)
		{
			write(1, current->key, ft_strlen(current->key));
			write(1, "=", 1);
			write(1, current-> value, ft_strlen(current-> value));
			write(1, "\n", 1);
			i++;
			if(current->next)
				current = current->next;
			else
				break;
		}
		j++;
	}
}

