/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 21:24:40 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	g_msh;

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		g_msh.error_code = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	read_cmd_line(char **cmd_line)
{
	char	*buffer;

	buffer = "\033[1;96mcoder@minishell $ \033[0m";
	*cmd_line = readline(buffer);
}

void	minishell_loop(void)
{
	char			*cmd_line;
	t_token_list	*tokens;

	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		read_cmd_line(&cmd_line);
		if (!cmd_line)
			exit_minishell();
		if (ft_strlen(cmd_line) == 0 || ft_isempty(cmd_line))
		{
			free(cmd_line);
			continue ;
		}
		add_history(cmd_line);
		tokens = ft_init_tokenize(cmd_line);
		if (!tokens)
		{
			free(cmd_line);
			return ;
		}
		syntax_analysis(tokens);
		free(cmd_line);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv)
	{
		msh_error(2, "minishell", "too many arguments.");
		exit_minishell();
	}
	alloc_hash_table(__environ);
	g_msh.error_code = 0;
	minishell_loop();
	return (0);
}
