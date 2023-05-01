/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/05/01 13:02:26 by mariana          ###   ########.fr       */
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
}

void	minishell_loop(void)
{
	char		*cmd_line;
	TokenList	*tokens;

	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0)
		{
			free(cmd_line);
			continue ;
		}
		add_history(cmd_line);
		tokens = ft_init_tokenize(cmd_line);
		if (!tokens)
			return ;
		for (int i = 0; i < tokens->count; i++) {
        	char *token_without_quotes = remove_outer_quotes(tokens->tokens[i]);
        	printf("Token %d: %s\n", i, token_without_quotes);
    	}
		execute(tokens, cmd_line);

    	// free_token_list(tokens);
		//expand(tokens);
		// free(tokens);
		// if (cmd_line)
		// 	free(cmd_line);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv)
		msh_error(2);
	alloc_hash_table(__environ);
	g_msh.error_code = 0;
	minishell_loop();
	//TODO: Perform cleanup
	return (0);
}
