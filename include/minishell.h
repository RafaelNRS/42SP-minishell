/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/27 09:01:31 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>

# define MSH_LINE_BUFFER_SIZE 1024
# define MSH_TOKEN_BUFFER_SIZE 64
# define MSH_TOKEN_DELIMITER " \t\r\n\a"
# define ENV_MAX_SIZE 2
# define TABLE_DEFAULT_SIZE 50

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

typedef	struct h_msh
{
	h_table	*env;
	h_table *local;
	int		error_code;
}	t_msh;

extern t_msh	g_msh;

void msh_error(int error_code);

// hash functions
h_table *create_table(int size);
h_item	*create_new_item(char *var);
int	hash_function(char *key, int size);
void free_item(h_item *item);
void	add_h_item(char *var, h_table *table);
h_table *alloc_hash_table(char **env);
void delete_item(h_table *table, char *key);
char *ht_search(h_table *table, char *key);
void print_table(h_table *hash_env);
void	free_hash_table(h_table *table);

char **ft_tokenize(char const *cmd_line, char separator);

void execute(char	**cmd);
#endif
