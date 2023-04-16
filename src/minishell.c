/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/16 19:32:40 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	read_cmd_line(char **cmd_line)
{
	char *buffer;

	buffer = "\033[1;96mminishell>";
	*cmd_line = readline(buffer);
}

void minishell_loop(void)
{
	char *cmd_line;
	char **tokens;
	h_table	*table;

	table = alloc_hash_table(__environ);
	
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (ft_strlen(cmd_line) == 0)
		{
			free(cmd_line);
			continue;
		}
		tokens = ft_tokenize(cmd_line, ' ');
		execute(tokens, table);
		free(tokens);
		if (cmd_line)
			free(cmd_line);
	}
	free_hash_table(table);
}

int main(int argc, char **argv)
{
	if (argc > 1 && argv)
		msh_error(2);
	//TODO: Load config files
	minishell_loop();

	//TODO: Perform cleanup
	return 0;
}
