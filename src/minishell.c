/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/03/21 09:10:46 by ranascim         ###   ########.fr       */
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
	buffer_size = MSH_BUFFER_SIZE;
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
}

void minishell_loop(void)
{
	char *cmd_line;
	//char **args;
	int status;
	
	status = 999;
	while (status == 999)
	{
		ft_printf("\033[1;96mminishell>");
		cmd_line = read_cmd_line();
		ft_printf("%s\n",cmd_line);
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
