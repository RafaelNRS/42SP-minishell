/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/16 16:39:43 by mariana          ###   ########.fr       */
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
		free(tokens);
		if (cmd_line)
			free(cmd_line);
	}
}

int main(int argc, char **argv)
{
	// h_table *table;

	if (argc > 1 && argv)
		msh_error(2);
	//TODO: Load config files
	minishell_loop();

	//TODO: Perform cleanup
	return 0;

	// table = alloc_hash_table(__environ);
	// // printf("found - %s", ht_search(table, "TERM_PROGRAM"));
	// add_h_item("test=a", table); // dif from "test='a'"
	// add_h_item("PWD=a", table);
	// delete_item(table, "PWD");
	// print_table(table);
	// to do delete table
}
