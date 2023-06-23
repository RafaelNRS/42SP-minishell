/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:01:47 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 09:50:17 by ranascim         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>

# define MSH_LINE_BUFFER_SIZE 1024
# define MSH_TOKEN_BUFFER_SIZE 64
# define MAX_TOKENS 256
# define TABLE_DEFAULT_SIZE 50

// symbols
# define PIPE 90		// |
# define REDIRECT 91	// >
# define REDIRECT_A 92	// >>
# define HEREDOC 93		// <<
# define INPUT 94		// <
# define SEMICOLON 95	// ;

// after symbols
# define FILE 96		// after >
# define FILE_A 97		// after >>
# define INPUT_FILE 98	// after <
# define END_OF_FILE 99	// after <<

// generic
# define STRING 100

# define IN 0
# define OUT 1

# define TRUE 1
# define FALSE 0

# define TMP_FILE "/tmp/tmp_file"

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
	int		error_code;
}	t_msh;

typedef struct s_token
{
	int					type;
	char				*token;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	int		count;
}	t_token_list;

typedef struct s_link_cmds
{
	char				**full_cmd;
	int					type;
	int					count;
	struct s_link_cmds	*next;
}	t_link_cmds;

typedef struct s_cmd_list
{
	t_link_cmds			*chained_cmds;
	struct s_link_cmds	*next;
}	t_cmd_list;

extern t_msh	g_msh;

void			msh_error(int error_code);

// hash functions
void			alloc_hash_table(char **env);
t_table			*create_table(int size);
void			add_t_item(char *var);
int				hash_function(char *key);
void			free_item(t_item *item);
void			delete_item(char *key);
void			print_table(void);
char			*ht_search(char *key);
void			free_hash_table(void);

// builtin
void			export(t_link_cmds	*var);
void			unset(t_link_cmds	*var);
void			env(void);
void			pwd(void);
void			msh_exit(char **argv);
void			cd(t_link_cmds	*cmd);
void			echo(t_link_cmds	*cmd);

void			exit_minishell(void);

void			execute(t_link_cmds *cmd, int *fd, bool flag);
int				syntax_analysis(t_token_list *tokens_lst);
t_link_cmds		*create_cmds(t_token_list *tokens_lst);
char			*ft_strappend(char *s1, char *s2, int space);
void			validate_tokens(t_token_list *tokens_lst);
char			*join_n_strs(int count, ...);

// void		expand(char *tokens);

void			ft_tokenize(
					char *input,
					t_token_list **list,
					bool quotes[2],
					char *token_start);
t_token_list	*ft_init_tokenize(char *input);
void	cleanup_token_list(t_token_list *list);
void	cleanup_chained_cmd(t_link_cmds *node);
char			*expand_variables(const char *input, bool is_single_quote);
bool			is_delimiter(char c);
bool			is_quote(char c);
char			*remove_outer_quotes(char *token);
#endif
