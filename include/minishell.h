/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/05/01 10:15:39 by mariana          ###   ########.fr       */
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
# define MAX_TOKENS 256
# define MSH_TOKEN_DELIMITER " \t\r\n\a"
# define ENV_MAX_SIZE 2
# define TABLE_DEFAULT_SIZE 50

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

typedef	struct h_msh
{
	t_table	*env;
	t_table *local;
	int		error_code;
}	t_msh;

typedef struct {
    char **tokens;
    int count;
} TokenList;

extern t_msh	g_msh;

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

// void	execute(char	**cmd, t_table *table, char *cmd_line);

void execute(char	**cmd, char *cmd_line);
void expand(char **tokens);

TokenList *ft_tokenize(char *input, TokenList *list, bool quotes[2], char *token_start);
TokenList *ft_init_tokenize(char *input);
char *expand_variables(const char *input, bool is_single_quote);
void free_token_list(TokenList *list);
bool is_delimiter(char c);
bool is_quote(char c);
char *remove_outer_quotes(char *token);

#endif
