/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:03:45 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 18:30:31 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buf;

	g_msh.error_code = 0;
	buf = getcwd(NULL, 0);
	ft_printf("%s\n", buf);
	free(buf);
}
