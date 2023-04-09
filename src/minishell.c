/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/08 23:56:34 by mariana          ###   ########.fr       */
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
		write(2, "Bolinha\n", 8);
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

char	*ft_copy_str(char *src)
{
	int		size;
	int		i;
	char	*copy_src;

	size = 0;
	size = ft_strlen(src);
	if (size == 0)
		return (NULL);
	i = 0;
	copy_src = (char *) malloc(sizeof(char) * size + 1);
	while (src[i])
	{
		copy_src[i] = src[i];
		i++;
	}
	copy_src[i] = '\0';
	return (copy_src);
}

void	create_new_item(char *var, h_table *table)
{
	char	**env_values;
	h_item	*new_item;

	env_values = ft_split(var, '=');   
	new_item = (h_item *)ft_calloc(sizeof(h_item), 1);
	if (!new_item)
		msh_error(2);
    new_item->key = ft_copy_str(env_values[0]);
    new_item->value = ft_copy_str(env_values[1]);
	free(env_values);
    new_item->next = NULL;
	if (!new_item->key || !new_item->value)
		msh_error(2);
	table->bucket_items[0] = new_item;
	printf("key %s\n", table->bucket_items[0]->key);
	printf("valye %s\n", table->bucket_items[0]->value);
}

h_table *create_table(int size)
{
	h_table			*new_table;
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

void alloc_hash_table(char **env)
{
	// int i;
	int size;
	h_table *table;

	size = 0;
	while (env[size])
		size++;
	table = create_table(size * 2);
	// i = 0;
	create_new_item(env[0], table);
	// while (env[i])
}

int main(int argc, char **argv)
{
	// h_table *hash_env;

	if (argc > 1 && argv)
		msh_error(2);

	//TODO: Load config files
	alloc_hash_table(__environ);

	// printf("size %d, count %d\n", hash_env->size, hash_env->count);

	// minishell_loop();

	//TODO: Perform cleanup
	return 0;
}
