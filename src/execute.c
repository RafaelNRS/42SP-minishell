/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/04/16 19:36:42 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(char *var, h_table *table)
{
    // falta implementar
    // test="a" = a
    // test='a' = a
    // D='a"c'"1" == a"c1
    //  E='a"c"'1  == a"c"1
    if (ft_strchr(var, '='))
        add_h_item(var, table);
}

void unset(char *var, h_table *table)
{
    delete_item(table, var);
}

void env(h_table *table)
{
    print_table(table);
}

void built_in(char **cmd, h_table *table)
{
    if (ft_strncmp(cmd[0], "export\0", 7) == 0)
        export(cmd[1], table);
    if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
        unset(cmd[1], table);
    if (ft_strncmp(cmd[0], "env\0", 4) == 0)
        env(table);
}

void execute(char	**cmd, h_table *table)
{
    built_in(cmd, table);
}
