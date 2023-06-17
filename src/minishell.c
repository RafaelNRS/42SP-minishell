/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/17 10:40:50 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	read_cmd_line(char **cmd_line)
{
	char	*buffer;

	buffer = "\033[1;96mguest@minishell $ \033[0m";
	*cmd_line = readline(buffer);
	// TODO: Show current working directory in the terminal, etc...
}

t_link_cmds	*create_chained_cmd(void)
{
	t_link_cmds	*list;

	list = malloc(sizeof(t_link_cmds));
	if (list)
	{
		list->full_cmd = NULL;
		list->type = 0;
		list->next = NULL;
	}
	return (list);
}

void	add_chained_cmd(t_link_cmds *list, char *full_cmd, int type, int count)
{
	t_link_cmds	*new_node;
	t_link_cmds	*tmp;
	char		**arr_full_cmd;

	arr_full_cmd = ft_split(full_cmd, ' ');
	if (list->full_cmd)
	{
		new_node = malloc(sizeof(t_link_cmds));
		if (new_node)
		{
			new_node->full_cmd = arr_full_cmd;
			new_node->type = type;
			new_node->next = NULL;
			new_node->count = count;
			tmp = list;
			while (tmp->next)
				tmp = list->next;
			tmp->next = new_node;
		}
	}
	else
	{
		list->full_cmd = arr_full_cmd;
		list->type = type;
		list->count = count;
	}
}

void	check_tokens(t_token *token, int i, int *error)
{
	int	type;

	type = token->type;
	if (type == PIPE)
	{
		if (i == 0 || !token->prev)
			*error = 2; // ft_printf("syntax error near unexpected token `|'")
		else if (token->prev->type != STRING && token->prev->type != FILE
			&& token->prev->type != FILE_A)
		*error = 2; // ft_printf("syntax error near unexpected token `|'")
	}
	else if (type == REDIRECT || type == REDIRECT_A
		|| type == INPUT || type == HEREDOC)
	{
		if (!token->next)
			*error = 1; // ft_printf("syntax error near unexpected token `\n'");
		else if (token->prev && token->prev->type != STRING)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == REDIRECT && token->next->type != FILE)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == REDIRECT_A && token->next->type != FILE_A)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == INPUT && token->next->type != INPUT_FILE)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
		else if (type == HEREDOC && token->next->type != END_OF_FILE)
			*error = 1; // ft_printf("syntax error near unexpected token `%d'", token->token)
	}
}

int	validate_tokens(t_token_list *tokens_lst)
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
		if (error != FALSE)
			break ;
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
	t_token		*token;
	int			current_type;
	t_link_cmds	*cmds;
	char		*full_cmd;
	int			count;

	token = tokens_lst->head;
	cmds = create_chained_cmd();
	current_type = token->type;
	count = 0;
	while (token)
	{
		full_cmd = NULL;
		while (token->token && current_type == token->type)
		{
			full_cmd = ft_strappend(full_cmd, token->token);
			count++;
			if (token->next)
				token = token->next;
			else
				break ;
		}
		add_chained_cmd(cmds, full_cmd, current_type, count);
		free(full_cmd);
		if (token->next)
			current_type = token->next->type;
		token = token->next;
		count = 0;
	}
	return (cmds);
}

int	chained_cmds_size(t_link_cmds *chained_cmds)
{
	int			size;
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

void	save_std_fds(int *std_fd)
{
	std_fd[IN] = dup(STDIN_FILENO);
	std_fd[OUT] = dup(STDOUT_FILENO);
	// close(std_fd[IN]);
	// close(std_fd[OUT]);
}

void	reset_std_fds(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
}

void	create_pipe(int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO); // vai entrar pelo old_pipe
	if (*old_pipe_in != IN)
		close(*old_pipe_in);
	pipe(new_pipe);
	dup2(new_pipe[OUT], STDOUT_FILENO); // new pipe é o out
	close(new_pipe[OUT]);
	*old_pipe_in = dup(new_pipe[IN]); // troco o old pipe in pelo new pipe
	close(new_pipe[IN]);
}

void	execute_cmds(t_link_cmds *chained_cmds, char *envp[])
{
	t_link_cmds	*current_cmd;
	int			fd[2];
	int			saved_stdin;

	current_cmd = chained_cmds;
	saved_stdin = dup(STDIN_FILENO);
	// int saved_stdout = dup(STDOUT_FILENO);
	while (current_cmd && current_cmd->next)
	{
		pipe(fd);
		execute(current_cmd, envp, fd, TRUE);
		current_cmd = current_cmd->next;
	}
	execute(current_cmd, envp, fd, FALSE);
	dup2(saved_stdin, STDIN_FILENO);
}

int	syntax_analysis(t_token_list *tokens_lst, char *envp[])
{
	int			error;
	t_link_cmds	*chained_cmds;

// talvez passar o erro p dentro da função;
	error = validate_tokens(tokens_lst);
	if (error != 0)
		return (error);
	chained_cmds = create_cmds(tokens_lst);
	execute_cmds(chained_cmds, envp);
	return (0);
}

void	minishell_loop(char *envp[])
{
	char			*cmd_line;
	t_token_list	*tokens;

	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0 || ft_isempty(cmd_line))
		{
			free(cmd_line);
			continue ;
		}
		add_history(cmd_line);
		tokens = ft_init_tokenize(cmd_line);
		if (!tokens)
			return ;
		syntax_analysis(tokens, envp);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	if (argc > 1 && argv)
		msh_error(2);
	alloc_hash_table(__environ);
	g_msh.error_code = 0;
	minishell_loop(envp);
	// TODO: Perform cleanup
	return (0);
}
