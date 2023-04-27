/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/04/27 08:15:14 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(char *var)
{
    // falta implementar
    // test="a" = a
    // test='a' = a
    // D='a"c'"1" == a"c1
    //  E='a"c"'1  == a"c"1
    if (ft_strchr(var, '='))
        add_h_item(var, g_msh.env);
}

void unset(char *var)
{
    delete_item(g_msh.env, var);
}

void env()
{
    print_table(g_msh.env);
}

void built_in(char **cmd)
{
    if (ft_strncmp(cmd[0], "export\0", 7) == 0)
        export(cmd[1]);
    if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
        unset(cmd[1]);
    if (ft_strncmp(cmd[0], "env\0", 4) == 0)
        env();
}

void execute(char	**cmd)
{
    built_in(cmd);
}
