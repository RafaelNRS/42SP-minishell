/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_n_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:36:51 by mariana           #+#    #+#             */
/*   Updated: 2023/06/19 23:38:14 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_n_strs(int count, ...)
{
	va_list	args;
	int		i;
	char	*str;
	char	*tmp_arg;

	va_start(args, count);
	i = 0;
	str = NULL;
	while (i < count)
	{
		tmp_arg = va_arg(args, char *);
		str = ft_strappend(str, tmp_arg, FALSE);
		i++;
	}
	va_end(args);
	return (str);
}
