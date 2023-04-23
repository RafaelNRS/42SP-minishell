/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/16 21:04:02 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

# define MSH_LINE_BUFFER_SIZE 1024
# define MSH_TOKEN_BUFFER_SIZE 64
# define MSH_TOKEN_DELIMITER " \t\r\n\a"
# define ENV_MAX_SIZE 2

typedef struct h_item
{
	char			*key;
	char			*value;
	struct h_item	*next;
}	h_item;

typedef struct h_table
{
	h_item	**bucket_items;
	int		size;
	int		count;
}	h_table;

void	msh_error(int error_code);

// hash functions
h_table	*create_table(int size);
h_item	*create_new_item(char *var);
int		hash_function(char *key, int size);
void	free_item(h_item *item);
void	add_h_item(char *var, h_table *table);
h_table	*alloc_hash_table(char **env);
void	delete_item(h_table *table, char *key);
char	*ht_search(h_table *table, char *key);
void	print_table(h_table *hash_env);
void	free_hash_table(h_table *table);

char	**ft_tokenize(char const *cmd_line, char separator);

void	execute(char	**cmd, h_table *table, char *cmd_line);
#endif
