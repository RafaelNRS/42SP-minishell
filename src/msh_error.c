/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:22:29 by mariana           #+#    #+#             */
/*   Updated: 2023/06/17 12:27:40 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_error(int error_code)
{
	if (error_code == 1)
		write(2, "minishell: Memory allocation error\n", 35);
	else if (error_code == 2)
		write(2, "minishell: Too many arguments\n", 30);
	else if (error_code == 3)
		write(2, "Max limit?\n", 10);
	else if (error_code == 4)
		ft_printf("syntax error near unexpected token `|'"); // erro 2
	else if (error_code == 5)
	{
		ft_printf("syntax error near unexpected token `\'");// erro 1
		// TODO esse erro deveria tb poder receber um token para descrever o erro
		// ft_printf("syntax error near unexpected token `%d'", token->token)
	}
	exit(1);
	//  TODO add o numero do erro em $? ?
}
