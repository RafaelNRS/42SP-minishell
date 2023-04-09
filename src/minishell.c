/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/09 14:16:20 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_error(int error_code)
{
	if (error_code == 1)
		write(2,"minishell: Memory allocation error\n",35);
	else if (error_code == 2)
		write(2,"minishell: Too many arguments\n",30);
	else if (error_code == 3)
		write(2, "Max limit?\n", 10);
	exit(1);
}

static void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		// ???
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	read_cmd_line(char **cmd_line)
{
	char *buffer;

	buffer = "\033[1;96mminishell>";
	*cmd_line = readline(buffer);
}

char **msh_split_line(char *line)
{
	int buffer_size;
	//int position;
	char **tokens;
	//char **token;

	buffer_size = MSH_TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char*) * buffer_size);
	//position = 0;
	if (!tokens)
		msh_error(1);
	// Needs a function to accept multiple delimiters
	// token = ft_strtok(line, MSH_TOKEN_DELIMITER);
	tokens = ft_split(line, ' ');
	// while (token != NULL)
	// {
	// 	tokens[position] = token[position];
	// 	position++;
	// }
	// tokens[position] = NULL;
	return tokens;
	// Needs a realloc() implementation if the position exceeds the buffer_size
}

void minishell_loop(void)
{
	char *cmd_line;

	while (true)
	{
		// ?signal?
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0)
		{
			free(cmd_line);
			continue;
		}
		if (cmd_line)
			free(cmd_line);
		exit(0);
	}
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

h_item	*create_new_item(char *var)
{
	char	**env_values;
	h_item	*new_item;

	env_values = ft_split(var, '=');   
	new_item = (h_item *)ft_calloc(sizeof(h_item), 1);
	if (!new_item)
		msh_error(2);
	new_item->key = ft_strdup(env_values[0]);
	if (env_values[1])
		new_item->value = ft_strdup(env_values[1]);
	else
		new_item->value = NULL;
    new_item->next = NULL;
	free(env_values);
	return (new_item);
}

void free_item(h_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	add_new_item(char *var, h_table *table)
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

h_table *create_table(int size)
{
	h_table			*new_table;
	int	i;

	new_table = (h_table *)ft_calloc(sizeof(h_table), 1);
	new_table->size = size;
	new_table->count = 0;
	// ????
	new_table->bucket_items = (h_item **)ft_calloc(sizeof(h_table), size);
	i = 0;
	while (i < size)
	{
		new_table->bucket_items[i] = NULL;
		i++;
	}
	return (new_table);
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
		add_new_item(env[i], table);
		i++;
	}
	return (table);
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
            printf("Key %d: %s, Value:%s\n", j, current->key, current-> value);
			i++;
			if(current->next)
				current = current->next;
			else
				break;
		}
		j++;
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
		if (strcmp(current->key, key) == 0)
			return current->value;
		else
			current = current->next;
	}
	if (!current)
		printf("command not found %s\n", key); // deveria fazer um exit
	return NULL;
}

int main(int argc, char **argv)
{
	h_table *hash_env;

	if (argc > 1 && argv)
		msh_error(2);

	//TODO: Load config files
	hash_env = alloc_hash_table(__environ);
	// print_table(hash_env);
	printf("found - %s", ht_search(hash_env, "TERM_PROGRAM"));

	// minishell_loop();

	//TODO: Perform cleanup
	return 0;
}
