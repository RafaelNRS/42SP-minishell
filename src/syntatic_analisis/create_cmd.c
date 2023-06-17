/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariana <mariana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:40:00 by mariana           #+#    #+#             */
/*   Updated: 2023/06/17 12:46:11 by mariana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tmp = list->next;
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

t_link_cmds	*create_cmds(t_token_list *tokens_lst)
{
	t_token		*token;
	int			current_type;
	t_link_cmds	*cmds;
	char		*full_cmd;
	int			count;

	// TODO refactor esse function pq está grande
	token = tokens_lst->head;
	cmds = create_chained_cmd();
	current_type = token->type;
	count = 0;
	while (token)
	{
		full_cmd = NULL;
		while (token->token && current_type == token->type)
		{
			full_cmd = ft_strappend(full_cmd, token->token);
			count++;
			if (token->next)
				token = token->next;
			else
				break ;
		}
		add_chained_cmd(cmds, full_cmd, current_type, count);
		free(full_cmd);
		if (token->next)
			current_type = token->next->type;
		token = token->next;
		count = 0;
	}
	return (cmds);
}
