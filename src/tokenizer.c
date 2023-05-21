/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:51:20 by ranascim          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:45 by ranascim         ###   ########.fr       */
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

bool	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<') || \
		(c1 == '>' && c2 == '>'));
}

static bool	is_builtin(char *token)
{
	if (!token)
		return (false);
	if (!(ft_strcmp(token, "echo\0")) || !(ft_strcmp(token, "cd\0")))
		return (true);
	if (!(ft_strcmp(token, "pwd")) || !(ft_strcmp(token, "export")))
		return (true);
	if (!(ft_strcmp(token, "unset")) || !(ft_strcmp(token, "env")))
		return (true);
	if (!(ft_strcmp(token, "exit")))
		return (true);
	return (false);
}

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

static void	insert_spaces(char *line, bool quote, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (is_quote(line[i]))
			quote = !quote;
		if (is_operator(line[i]) && quote == false)
		{
			if (line[i] == '|')
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
		i++;
	}
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

void	free_token_list(t_tk_lst *list)
{
	int	i;

	i = 0;
	while (i < list->count)
	{
		free(list->tokens[i]);
		i++;
	}
	free(list->tokens);
	free(list);
}

void	copy_variable_value(char *var_name, char **out_ptr)
{
	char	*var_value;

	var_value = getenv(var_name);
	if (var_value)
	{
		ft_strlcpy(*out_ptr, var_value, ft_strlen(var_value) + 1);
		*out_ptr += ft_strlen(var_value);
	}
}

void	handle_var_exp(const char **in_ptr, char *var, char **out, bool s_quote)
{
	char	*var_name_ptr;

	if (**in_ptr == '$' && !s_quote && ft_isalnum(*(*in_ptr + 1)))
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

t_tk_lst	*ft_tokenize(char *p, t_tk_lst *list, bool quotes[2], char *t_st)
{
	list = malloc(sizeof(t_tk_lst));
	list->tokens = malloc(sizeof(char *) * MAX_TOKENS);
	list->count = 0;
	while (*p)
	{
		quotes[0] = check_s_quote(p, quotes);
		quotes[1] = check_d_quote(p, quotes);
		if (is_delimiter(*p) && !quotes[0] && !quotes[1])
		{
			if (t_st)
			{
				*p = '\0';
				if (list->count < MAX_TOKENS)
					list->tokens[list->count++] = expand_variables(t_st, false);
				t_st = NULL;
			}
		}
		else if (!t_st)
			t_st = p;
		p++;
	}
	if (t_st && list->count < MAX_TOKENS)
		list->tokens[list->count++] = expand_variables(t_st, false);
	return (list);
}

t_tk_tp_lst *new_token_list(void)
{
	t_tk_tp_lst *list = malloc(sizeof(t_tk_tp_lst));
	if (list)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	return list;
}

t_token *new_token(char *token)
{
	t_token *node = malloc(sizeof(t_token));
	if (node)
	{
		node->token = token;
		node->next = NULL;
		node->prev = NULL;
	}
	return node;
}

void add_token(t_tk_tp_lst *list, t_token *node)
{
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
	if (!(ft_strcmp(token, "|")))
		return (PIPE);
	if (is_double_operator(token, token+1))
		if (!(ft_strcmp(token, ">")))
			return (REDIRECT_A);
		if (!(ft_strcmp(token, "<")))
			return (HEREDOC);
	if (!(ft_strcmp(token, ">")))
		return (REDIRECT);
	if (!(ft_strcmp(token, "<")))
		return (INPUT);
	return (false);
}

static int	define_type(t_token **token)
{
	int	prev_type;

	if (token->prev && token->prev->type)
		prev_type = token->prev->type;
	if (is_builtin(token->token) && prev_type != REDIRECT && \
		prev_type != REDIRECT_A && prev_type != INPUT && prev_type != HEREDOC)
		token->type = BUILTIN;
	else if (is_operator(token->token))
		token->type = define_operator(token->token);
	else if (prev_type == REDIRECT)
		token->type = FILE;
	else
		token->type = BUILTIN;
}

t_tk_lst	*ft_init_tokenize(char *input)
{
	t_tk_lst	*list;
	t_tk_tp_lst	*token_list;
	t_token		*token;
	bool		quotes[2];
	char		*token_start;
	int			len;

	token_list = new_token_list();
	if (!token_list)
		return (NULL);
	len = ft_strlen(input);
	token_start = NULL;
	list = NULL;
	quotes[0] = false;
	quotes[1] = false;
	insert_spaces(input, false, len);
	list = ft_tokenize(input, list, quotes, token_start);
	for (int i = 0; i < list->count; i++) {
        remove_outer_quotes(list->tokens[i]);
        printf("Token %d: %s\n", i, list->tokens[i]);
		token = new_token(list->tokens[i]);
		add_token(token_list, token);
		token->type = define_type(&token);
    }
	
	return (list);
}
