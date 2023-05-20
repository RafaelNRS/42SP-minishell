/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/05/20 11:27:00 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>

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

typedef struct h_msh
{
	t_table	*env;
	t_table	*local;
	int		error_code;
}	t_msh;

typedef struct s_tk_lst
{
	char	**tokens;
	int		count;
}	t_tk_lst;

typedef struct s_tk_type
{
	int					type;
	char				*token;
	struct t_token_type	*next;
	struct t_token_type *previous;
}	t_tk_type;

extern t_msh	g_msh;

void		msh_error(int error_code);

// hash functions
void		alloc_hash_table(char **env);
t_table		*create_table(int size);
void		add_t_item(char *var);
int			hash_function(char *key);
void		free_item(t_item *item);
void		delete_item(char *key);
void		print_table(void);
char		*ht_search(char *key);
void		free_hash_table(void);

// builtin
void		export(t_tk_lst *var);
void		unset(t_tk_lst *var);
void		env(void);
void		pwd(t_tk_lst *cmd);
void		exit_minishell(void);
int			args_count(char **args);
void		cd(t_tk_lst *cmd);
void		echo(t_tk_lst *cmd);

void		execute(t_tk_lst *cmd);
void		expand(t_tk_lst *tokens);

t_tk_lst	*ft_tokenize(
				char *input,
				t_tk_lst *list,
				bool quotes[2],
				char *token_start);
t_tk_lst	*ft_init_tokenize(char *input);
char		*expand_variables(const char *input, bool is_single_quote);
void		free_token_list(t_tk_lst *list);
bool		is_delimiter(char c);
bool		is_quote(char c);
char		*remove_outer_quotes(char *token);
#endif
