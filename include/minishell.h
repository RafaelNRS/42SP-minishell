/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/23 13:52:23 by mariana          ###   ########.fr       */
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

typedef struct t_item
{
	char			*key;
	char			*value;
	struct t_item	*next;
}	t_item;

typedef struct t_table
{
	t_item	**bucket_items;
	int		size;
	int		count;
}	t_table;

void	msh_error(int error_code);

// hash functions
t_table	*create_table(int size);
t_item	*create_new_item(char *var);
int		hash_function(char *key, int size);
void	free_item(t_item *item);
void	add_t_item(char *var, t_table *table);
t_table	*alloc_hash_table(char **env);
void	delete_item(t_table *table, char *key);
char	*ht_search(t_table *table, char *key);
void	print_table(t_table *hash_env);
void	free_hash_table(t_table *table);

char	**ft_tokenize(char const *cmd_line, char separator);

void	execute(char	**cmd, t_table *table, char *cmd_line);
#endif
