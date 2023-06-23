/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:57:55 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 10:24:25 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *c)
{
	while (*c)
	{
		if (!ft_isdigit(*c++))
			return (FALSE);
	}
	return (TRUE);
}

void	exit_minishell()
{
	
}

void	msh_exit(char **argv)
{
	int ret_code;

	ret_code = 0;
	if (argv[1] && !is_number(argv[1]))
		msh_error(1);
		// msh_error("exit: numeric argument required");
	else if (argv[2])
		msh_error(1);
		// msh_error("exit: too many arguments");
	else if (argv[1])
		ret_code = ft_atoi(argv[1]);
	ft_printf("exit - %d\n", ret_code);
	// se mandar mais argumentos
	// syntax error near unexpected token `2' -> exit(2) senao funfa normal
	// free(cmd);
	// free_hash_table();
	// if (cmd_line)
	// 	free(cmd_line);
	exit_minishell();
}
