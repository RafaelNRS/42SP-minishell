/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/09 18:47:39 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh g_msh;

static void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void read_cmd_line(char **cmd_line)
{
	char *buffer;

	buffer = "\033[1;96mguest@minishell $ \033[0m";
	*cmd_line = readline(buffer);
	// TODO: Show current working directory in the terminal, etc...
}

t_link_cmds *create_chained_cmd(void)
{
	t_link_cmds *list;

	list = malloc(sizeof(t_link_cmds));
	if (list)
	{
		list->full_cmd = NULL;
		list->cmd = NULL;
		list->type = 0;
		list->next = NULL;
	}
	return (list);
}

void add_chained_cmd(t_link_cmds *list, char *full_cmd, char *cmd, int type)
{
	t_link_cmds *new_node;

	if (list->full_cmd)
	{
		new_node = malloc(sizeof(t_link_cmds));
		if (new_node)
		{
			new_node->full_cmd = full_cmd;
			new_node->cmd = cmd;
			new_node->type = type;
			new_node->next = NULL;
			list->next = new_node;
		}
	}
	else
	{
		list->full_cmd = full_cmd;
		list->cmd = cmd;
		list->type = type;
	}
}

void check_tokens(t_token	*token, int i, int *error)
{
	int		type;

	type = token->type;
	if (type == PIPE)
	{
		if (i == 0 || !token->prev)
			*error = 2; // ft_printf("syntax error near unexpected token `|'")
		else if (token->prev->type != STRING && token->prev->type != FILE &&
			token->prev->type != FILE_A)
			*error = 2; // ft_printf("syntax error near unexpected token `|'")
	}
	else if (type == REDIRECT || type == REDIRECT_A ||
		type == INPUT || type == HEREDOC)
	{
		if (!token->next)
			*error = 1;	  // ft_printf("syntax error near unexpected token `\n'");
		else if (token->prev && token->prev->type != STRING)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == REDIRECT && token->next->type != FILE) 		// > 91-96
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == REDIRECT_A && token->next->type != FILE_A) 	// >> 92-97
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == INPUT && token->next->type != INPUT_FILE) 		// < 94-98
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == HEREDOC && token->next->type != END_OF_FILE) 	// << 93-99
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
	}

	// cat < ping | grep m > test | cat < ping | grep m só retorno o ultimo comando
}

int validate_tokens(t_token_list *tokens_lst)
{
	t_token	*token;
	int		i;
	int		error;

	token = tokens_lst->head;
	i = 0;
	error = FALSE;
	while (i < tokens_lst->count)
	{
		check_tokens(token, i, &error);
		// if (type == SEMICOLON && token->next)
		// 	check_tokens(token, i, &error);
		if (error != FALSE)
			break;
		if (token->next)
			token = token->next;
		i++;
	}
	return (error);
}

char	*ft_strappend(char *s1, char *s2)
{
	char	*new_string;
	size_t	len;
	size_t	s1_len;
	size_t	i;
	size_t	z;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2) + 1;
	new_string = (char *) malloc((len * sizeof(char)));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	if (s1)
	{
		new_string[i] = ' ';
		i++;
	}
	z = 0;
	while (s2[z])
		new_string[i++] = s2[z++];
	free(s1);
	new_string[i] = '\0';
	return (new_string);
}

t_link_cmds	*create_cmds(t_token_list *tokens_lst)
{
	t_token	*token;
	int current_type;
	t_link_cmds	*cmds;
	char *full_cmd;
	char *cmd;

	token = tokens_lst->head;
	cmds = create_chained_cmd();
	current_type = token->type;
	while (token)
	{
		full_cmd = '\0';
		cmd = token->token;
		while (token && current_type == token->type)
		{
			full_cmd = ft_strappend(full_cmd, token->token);
			if (token->next)
				token = token->next;
			else
				break;
			// i++;
		}
		add_chained_cmd(cmds, full_cmd, cmd, current_type);
		token = token->next;
		current_type = token->type;
	}
	return (cmds);
}

void create_pipe(int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO); // vai entrar pelo old_pipe
	if (*old_pipe_in != 0)
		close(*old_pipe_in);
	pipe(new_pipe);
	dup2(new_pipe[OUT], STDOUT_FILENO); // new pipe é o out
	close(new_pipe[OUT]);
	*old_pipe_in = dup(new_pipe[IN]); // troco o old pipe in pelo new pipe
	close(new_pipe[IN]);
}

int chained_cmds_size(t_link_cmds *chained_cmds)
{
	int size;
	t_link_cmds	*tmp;

	tmp = chained_cmds;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	exec_cmd(t_link_cmds	*cmd)
{
	ft_printf("exec %s\n", cmd->full_cmd);
}

void bolinha(t_link_cmds	*cmd)
{
	// ft_printf("cmds %s, %d\n", cmd->full_cmd, cmd->type);

// se tiver um = deveria setar uma variavel

	if (cmd->type == STRING)
		exec_cmd(cmd);
		// checar se é builtin ou comando e executar
	// else if (cmd->type == REDIRECT)
	// else if (cmd->type == REDIRECT_A)
	// else if (cmd->type == INPUT_A)
	// else if (cmd->type == INPUT)

}

void execute_cmds(t_link_cmds *chained_cmds)
{
	int size;
	t_link_cmds	*current;
	int old_pipe_in;

	size = chained_cmds_size(chained_cmds);
	// ft_printf("%d", size);

	old_pipe_in = 0;
	int		save_fd[2];
	save_fd[IN] = dup(STDIN_FILENO);
	save_fd[OUT] = dup(STDOUT_FILENO);

	// current = chained_cmds;
	if (size > 1)
		create_pipe(old_pipe_in);

	while(chained_cmds)
	{
		// tratar direcionamento in e out;
		bolinha(chained_cmds);
		current = current->next;
		dup2(save_fd[IN], STDIN_FILENO);
		close(save_fd[IN]);
		dup2(save_fd[OUT], STDOUT_FILENO);
		close(save_fd[OUT]);
	}
	// free(chained_cmds);
}

// int syntax_analysis(t_cmd_list **cmds_list, t_token_list *tokens_lst)
int syntax_analysis(t_token_list *tokens_lst)
{
	int error;
	t_link_cmds	*chained_cmds;

	error = validate_tokens(tokens_lst);
	if (error != 0)
		return (error);

	// int i;
	// i = 0;
	// t_link_cmds *cmds;

	chained_cmds = create_cmds(tokens_lst);

	execute_cmds(chained_cmds);
	// free(chained_cmds)
	return (0);

	// full_comand

	// cmds_list = new_cmd_list();
	// if (!cmds_list)
	// 	return (NULL);
	
	// 		if (!cmds_list)
	// 		{
	// 			t_cmd *cmd;
	// 			t_cmd *prev;
	// 			t_token *next_token;

	// 			cmd = new_cmd(token, NULL);
	// 			add_cmd(cmds_list, cmd, token->type, NULL);
	// 			while (y < i)
	// 			{
	// 				next_token = token->next;
	// 				prev = cmd;
	// 				cmd = new_cmd(next_token, token);
	// 				token->next
	// 				y++;
	// 			}
	// 		}
	// 	}

}

void minishell_loop(void)
{
	char *cmd_line;
	t_token_list *tokens;
	t_token *token;
	// t_cmd_list *cmds_list;
	// int syntax_analysis_error;

	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0 || ft_isempty(cmd_line))
		{
			free(cmd_line);
			continue;
		}
		add_history(cmd_line);
		tokens = ft_init_tokenize(cmd_line);
		if (!tokens)
			return;

		token = tokens->head;
		while (token != NULL)
		{
			printf("-> %s, Type %d\n", token->token, token->type);
			token = token->next;
		}
		// syntax_analysis(tokens);
		ft_printf("erro %d\n", syntax_analysis(tokens));
		// syntax_analysis_error = syntax_analysis(&cmds_list, tokens);
		// if (syntax_analysis_error != FALSE)
		// 	ft_printf("deu erro!!!");
		// execute_commands(tokens);
		// printf("Total tokens: %d\n",tokens->count);
		// execute(tokens);

		// free_token_list(tokens);
		// expand(tokens);
		// free(tokens);
		// if (cmd_line)
		// 	free(cmd_line);
	}
}

int main(int argc, char **argv)
{
	if (argc > 1 && argv)
		msh_error(2);
	alloc_hash_table(__environ);
	g_msh.error_code = 0;
	minishell_loop();
	// TODO: Perform cleanup
	return (0);
}

