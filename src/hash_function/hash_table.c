/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:17:03 by mariana           #+#    #+#             */
/*   Updated: 2023/05/01 13:03:18 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_hash_table(char **env)
{
	int		i;
	int		size;

	size = 0;
	while (env[size])
		size++;
	g_msh.env = create_table(size * 2);
	i = 0;
	while (env[i])
	{
		add_t_item(env[i]);
		i++;
	}
}

char	*ht_search(char *key)
{
	int		index;
	t_item	*current;

	index = hash_function(key);
	current = g_msh.env->bucket_items[index];
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->value);
		else
			current = current->next;
	}
	if (!current)
		ft_printf("command not found %s\n", key);
	return (NULL);
}

void	print_table(void)
{
	int		i;
	int		j;
	t_item	*current;

	i = 0;
	j = 0;
	while (i < g_msh.env->count)
	{
		current = g_msh.env->bucket_items[j];
		while (current)
		{
			ft_printf("%s=%s\n", current->key, current-> value);
			i++;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		j++;
	}
}
