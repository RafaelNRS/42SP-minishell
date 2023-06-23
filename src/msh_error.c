/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:22:29 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:27:49 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_error(int error_code, char *cmd, char *message)
{
	g_msh.error_code = error_code;
	ft_printf("%s: %s\n", cmd, message);
}
