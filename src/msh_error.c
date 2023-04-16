/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.C                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:22:29 by mariana           #+#    #+#             */
/*   Updated: 2023/04/09 21:22:48 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_error(int error_code)
{
	if (error_code == 1)
		write(2,"minishell: Memory allocation error\n",35);
	else if (error_code == 2)
		write(2,"minishell: Too many arguments\n",30);
	else if (error_code == 3)
		write(2, "Max limit?\n", 10);
	exit(1);
}
