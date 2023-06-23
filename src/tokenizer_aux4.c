/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:41:49 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/23 20:42:10 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(const char *in_ptr, bool is_single_quote)
{
	char	*output;
	char	*out_ptr;
	char	var_name[256];

	output = malloc(4096);
	if (!output)
		return (NULL);
	out_ptr = output;
	is_single_quote = (in_ptr[0] == '\'');
	while (*in_ptr)
		handle_var_exp(&in_ptr, var_name, &out_ptr, is_single_quote);
	*out_ptr = '\0';
	return (output);
}

t_token_list	*new_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (list)
	{
		list->head = NULL;
		list->tail = NULL;
		list->count = 1;
	}
	return (list);
}

t_token	*new_token(char *token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node)
	{
		node->token = token;
		node->next = NULL;
		node->prev = NULL;
		node->type = 0;
	}
	return (node);
}

void	cleanup_token_list(t_token_list *list)
{
	t_token	*node;
	t_token	*next_node;

	node = list->head;
	while (node)
	{
		next_node = node->next;
		if (node->token)
			free(node->token);
		free(node);
		node = next_node;
	}
	free(list);
}

void	add_token(t_token_list *list, t_token *node)
{
	remove_outer_quotes(node->token);
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
}
