/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:31:27 by ranascim          #+#    #+#             */
/*   Updated: 2023/03/21 07:57:52 by ranascim         ###   ########.fr       */
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
	int c;

	buffer_size = MSH_BUFFER_SIZE;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		msh_error(1);
	position = 0;

	while(1)
	{
		
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
