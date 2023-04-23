/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:57:01 by mariana           #+#    #+#             */
/*   Updated: 2023/04/23 13:48:36 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// falta implementar
// test="a" = a
// test='a' = a
// D='a"c'"1" == a"c1
//  E='a"c"'1  == a"c"1

void	export(char *var, t_table *table)
{
	if (ft_strchr(var, '='))
		add_t_item(var, table);
}

void	unset(char *var, t_table *table)
{
	delete_item(table, var);
}

void	env(t_table *table)
{
	print_table(table);
}

void	pwd(t_table *table)
{
	char	*value;

	value = ht_search(table, "PWD");
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
}

// print only string
// void echo(char **cmd)
// {
//     int i;
//     int has_flag;

//     i = 1;
//     has_flag = 0;
//     if (cmd[i])
//     {
//         if (ft_strncmp(cmd[i], "-n", 3) == 0)
//         {
//             i++;
//             has_flag++;
//         }
//         write(2, cmd[i], ft_strlen(cmd[i]));
//         if (has_flag)
//         {

//         }
//         else
//     }
//     else
//         write(2, "\n", 1);
// }

void	ft_exit(char **cmd, t_table *table, char *cmd_line)
{
	free(cmd);
	free_hash_table(table);
	if (cmd_line)
		free(cmd_line);
	exit(1);
}

void	built_in(char **cmd, t_table *table, char *cmd_line)
{
	if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		export(cmd[1], table);
	if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		unset(cmd[1], table);
	if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		env(table);
	if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		pwd(table);
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		ft_exit(cmd, table, cmd_line);
	// if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
	//     echo(cmd);
}

void	execute(char **cmd, t_table *table, char *cmd_line)
{
	built_in(cmd, table, cmd_line);
}
