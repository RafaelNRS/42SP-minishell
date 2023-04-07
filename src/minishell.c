/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/07 00:41:58 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_error(int error_code)
{
	if (error_code == 1)
	{
		write(2,"minishell: Memory allocation error\n",35);
		exit(1);
	}
}

char *read_cmd_line(void)
{
	int buffer_size;
	int position;
	char *buffer;
	int *c;

	position = 0;
	buffer_size = MSH_LINE_BUFFER_SIZE;
	buffer = malloc(sizeof(char) * buffer_size);
	c = malloc(sizeof(int) * 1);
	if (!buffer || !c)
		msh_error(1);
	while(1)
	{
		read(0, c, 1);
		if (c[0] == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		buffer[position] = c[0];
		position++;
	}
	// Needs a realloc() implementation if the position exceeds the buffer_size
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
	char **tokens;
	//char **args;
	int status;
	int i;
	
	i = 0;
	status = 999;
	while (status == 999)
	{
		ft_printf("\033[1;96mminishell>");
		cmd_line = read_cmd_line();
		ft_printf("%s\n",cmd_line);
		tokens = msh_split_line(cmd_line);
		while (tokens[i])
		{
			ft_printf("Token %d: %s\n",i, tokens[i]);
			i++;
		} 
		status = 0;
	}
}

int main(void)
{
	//TODO: Load config files
	minishell_loop();
	
	//TODO: Perform cleanup
	return 0;
}
