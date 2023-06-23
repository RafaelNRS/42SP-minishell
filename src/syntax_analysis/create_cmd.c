/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/23 19:50:40 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_chained_cmd(t_link_cmds *node)
{
	t_link_cmds	*next_node;
	t_link_cmds	*tmp_node;
	int			i;

	next_node = node;
	while (next_node)
	{
		i = 0;
		tmp_node = next_node->next;
		if (next_node->full_cmd)
		{
			while (i <= next_node->count)
			{
				free(next_node->full_cmd[i]);
				i++;
			}
			free(next_node->full_cmd);
		}
		free(next_node);
		next_node = tmp_node;
	}
}

t_link_cmds	*create_chained_cmd(void)
{
	t_link_cmds	*list;

	list = malloc(sizeof(t_link_cmds));
	if (list)
	{
		list->full_cmd = NULL;
		list->type = 0;
		list->next = NULL;
	}
	return (list);
}

void	create_new_node(t_link_cmds *list, char **cmd, int type, int count)
{
	t_link_cmds	*new_node;
	t_link_cmds	*tmp;

	new_node = malloc(sizeof(t_link_cmds));
	if (new_node)
	{
		new_node->full_cmd = cmd;
		new_node->type = type;
		new_node->next = NULL;
		new_node->count = count;
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	add_chained_cmd(t_link_cmds *list, char *full_cmd, int type, int count)
{
	char		**arr_full_cmd;

	arr_full_cmd = ft_split(full_cmd, ' ');
	if (list->full_cmd)
		create_new_node(list, arr_full_cmd, type, count);
	else
	{
		list->full_cmd = arr_full_cmd;
		list->type = type;
		list->count = count;
	}
}

t_link_cmds	*create_cmds(t_link_cmds *cmds, int ct, t_token *token, int c_type)
{
	char		*full_cmd;

	while (token)
	{
		full_cmd = NULL;
		while (token && token->token && c_type == token->type)
		{
			full_cmd = ft_strappend(full_cmd, token->token, TRUE);
			ct++;
			if (token->next)
				token = token->next;
			else
				break ;
		}
		add_chained_cmd(cmds, full_cmd, c_type, ct);
		if (token->type == SEMICOLON)
			add_chained_cmd(cmds, "SEMICOLON", SEMICOLON, 1);
		free(full_cmd);
		if (token->next)
			c_type = token->next->type;
		token = token->next;
		ct = 0;
	}
	return (cmds);
}
