/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/08 10:05:27 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_error(int error_code)
{
	if (error_code == 1)
		write(2,"minishell: Memory allocation error\n",35);
	else if (error_code == 2)
		write(2,"minishell: Too many arguments\n",30);

	exit(1);
}

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
	//ft_printf("\033[1;96mminishell>");
	*cmd_line = readline(buffer);
	//free(buffer);
}

char **msh_split_line(char *line)
{
	int buffer_size;
	//int position;
	char **tokens;
	//char **token;

	buffer_size = MSH_TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char*) * buffer_size);
	//position = 0;
	if (!tokens)
		msh_error(1);
	// Needs a function to accept multiple delimiters
	// token = ft_strtok(line, MSH_TOKEN_DELIMITER);
	tokens = ft_split(line, ' ');
	// while (token != NULL)
	// {
	// 	tokens[position] = token[position];
	// 	position++;
	// }
	// tokens[position] = NULL;
	return tokens;
	// Needs a realloc() implementation if the position exceeds the buffer_size
}

void minishell_loop(void)
{
	char *cmd_line;
	//char **tokens;
	//int status;
	//int i;
	
	//i = 0;
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
		// ft_printf("%s\n",cmd_line);
		// tokens = msh_split_line(cmd_line);
		// while (tokens[i])
		// {
		// 	ft_printf("Token %d: %s\n",i, tokens[i]);
		// 	i++;
		// }
		if (cmd_line)
			free(cmd_line);
		exit(0);
	}
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
