/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:51:20 by ranascim          #+#    #+#             */
/*   Updated: 2023/06/09 17:21:31 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_semi(char c)
{
	return (c == ';');
}

bool	ft_isalnumvar(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == '?');
}

bool	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<') || \
		(c1 == '>' && c2 == '>'));
}

// static bool	is_builtin(char *token)
// {
// 	if (!token)
// 		return (false);
// 	if (!(ft_strncmp(token, "echo\0", 5)) || !(ft_strncmp(token, "cd\0", 3)))
// 		return (true);
// 	if (!(ft_strncmp(token, "pwd", 3)) || !(ft_strncmp(token, "export", 6)))
// 		return (true);
// 	if (!(ft_strncmp(token, "unset", 5)) || !(ft_strncmp(token, "env", 3)))
// 		return (true);
// 	if (!(ft_strncmp(token, "exit", 4)))
// 		return (true);
// 	return (false);
// }

static void	shift_characters_right(char *line, int start, int len)
{
	int	i;

	i = len;
	while (i >= start)
	{
		line[i + 1] = line[i];
		i--;
	}
}

static void	insert_single_operator_spaces(char *line, int index, int len)
{
	if (line[index + 1] != ' ' && line[index + 1] != '\0')
	{
		shift_characters_right(line, index, len);
		line[index + 1] = ' ';
	}
	if (line[index - 1] != ' ' && index > 0)
	{
		shift_characters_right(line, index - 1, len);
		line[index] = ' ';
	}
}

static void	insert_double_operator_spaces(char *line, int index, int len)
{
	if (line[index + 2] != ' ' && line[index + 2] != '\0')
	{
		shift_characters_right(line, index + 1, len);
		line[index + 2] = ' ';
	}
	if (line[index - 1] != ' ' && index > 0)
	{
		shift_characters_right(line, index - 1, len);
		line[index] = ' ';
	}
}

static void	insert_spaces(char *line, bool quote, int len, int i)
{
	while (i < len)
	{
		if (is_quote(line[i]))
			quote = !quote;
		if ((is_operator(line[i]) && quote == false) || is_semi(line[i]))
		{
			if (line[i] == '|' || line[i] == ';')
				insert_single_operator_spaces(line, i, len);
			else if (line[i] == '<' || line[i] == '>')
			{
				if (is_double_operator(line[i], line[i + 1]))
				{
					insert_double_operator_spaces(line, i, len);
					i += 2;
				}
				else
					insert_single_operator_spaces(line, i, len);
			}
		}
		len = ft_strlen(line);
		i++;
	}
	line[len] = '\0';
}

bool	check_s_quote(char *input, bool quotes[2])
{
	if (*input == '\'' && !quotes[1])
		return (!quotes[0]);
	else
		return (quotes[0]);
}

bool	check_d_quote(char *input, bool quotes[2])
{
	if (*input == '\"' && !quotes[0])
		return (!quotes[1]);
	else
		return (quotes[1]);
}

char	*remove_outer_quotes(char *str)
{
	int		len;
	char	*result;
	int		i;
	char	quote;

	i = 0;
	result = str;
	len = strlen(str);
	while (i < len)
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (i < len && str[i] != quote)
				*result++ = str[i++];
			if (i < len)
				i++;
		}
		else
			*result++ = str[i++];
	}
	*result = '\0';
	return (str);
}

void	copy_variable_value(char *var_name, char **out_ptr)
{
	char	*var_value;

	if (var_name[0] != '?')
		var_value = getenv(var_name);
	else
		var_value = ft_itoa(g_msh.error_code);
	if (var_value)
	{
		ft_strlcpy(*out_ptr, var_value, ft_strlen(var_value) + 1);
		*out_ptr += ft_strlen(var_value);
	}
}

void	handle_var_exp(const char **in_ptr, char *var, char **out, bool s_quote)
{
	char	*var_name_ptr;

	if (**in_ptr == '$' && !s_quote && ft_isalnumvar(*(*in_ptr + 1)))
	{
		(*in_ptr)++;
		var_name_ptr = var;
		while (**in_ptr && (!is_quote(**in_ptr) && !is_delimiter(**in_ptr)))
			*var_name_ptr++ = *(*in_ptr)++;
		*var_name_ptr = '\0';
		copy_variable_value(var, out);
	}
	else
		*(*out)++ = *(*in_ptr)++;
}

char	*expand_variables(const char *in_ptr, bool is_single_quote)
{
	char	*output;
	char	*out_ptr;
	char	var_name[256];

	output = malloc(4096);
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
		list->count = 0;
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

static int	define_operator(char *token)
{
	if (!(ft_strncmp(token, "|", 1)))
		return (PIPE);
	if (is_double_operator(token[0], token[1]))
	{
		if (!(ft_strncmp(token, ">", 1)))
			return (REDIRECT_A);
		if (!(ft_strncmp(token, "<", 1)))
			return (HEREDOC);
	}
	if (!(ft_strncmp(token, ">", 1)))
		return (REDIRECT);
	if (!(ft_strncmp(token, "<", 1)))
		return (INPUT);
	return (false);
}

static void	define_type(t_token **token)
{
	int	prev_type;

	if ((*token)->prev && (*token)->prev->type)
		prev_type = (*token)->prev->type;
	if (is_operator((*token)->token[0]))
		(*token)->type = define_operator((*token)->token);
	else if (is_semi((*token)->token[0]))
		(*token)->type = SEMICOLON;
	else if (prev_type == REDIRECT)
		(*token)->type = FILE;
	else if (prev_type == REDIRECT_A)
		(*token)->type = FILE_A;
	else if (prev_type == INPUT)
		(*token)->type = INPUT_FILE;
	else if (prev_type == HEREDOC)
		(*token)->type = END_OF_FILE;
	else
		(*token)->type = STRING;
}

void	ft_tokenize(char *p, t_token_list **list, bool quotes[2], char *t_st)
{
	while (*p)
	{
		quotes[0] = check_s_quote(p, quotes);
		quotes[1] = check_d_quote(p, quotes);
		if (is_delimiter(*p) && !quotes[0] && !quotes[1])
		{
			if (t_st)
			{
				*p = '\0';
				if ((*list)->count++ < MAX_TOKENS)
					add_token((*list), \
					new_token(expand_variables(t_st, false)));
				t_st = NULL;
			}
		}
		else if (!t_st)
			t_st = p;
		p++;
	}
	if (t_st && (*list)->count++ < MAX_TOKENS)
		add_token((*list), new_token(expand_variables(t_st, false)));
}

static void	define_types(t_token_list **list)
{
	t_token	*current;

	current = (*list)->head;
	while (current != NULL)
	{
		define_type(&current);
		current = current -> next;
	}
}

t_token_list	*ft_init_tokenize(char *input)
{
	t_token_list	*list;
	bool			quotes[2];
	char			*token_start;
	int				len;
	int				i;

	i = 0;
	list = new_token_list();
	if (!list)
		return (NULL);
	len = ft_strlen(input);
	token_start = NULL;
	quotes[0] = false;
	quotes[1] = false;
	insert_spaces(input, false, len, i);
	ft_tokenize(input, &list, quotes, token_start);
	define_types(&list);
	return (list);
}
