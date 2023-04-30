/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranascim <ranascim@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:06:21 by ranascim          #+#    #+#             */
/*   Updated: 2023/04/28 14:48:51 by ranascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_delimiter(char c) {
    return c == ' '|| c == '\t' || c == '\n';
}

bool is_quote(char c) {
    return c == '\'' || c == '\"';
}

char *remove_outer_quotes(char *token) {
    int len = strlen(token);

    if (len >= 2 && is_quote(token[0]) && token[0] == token[len - 1]) {
        memmove(token, token + 1, len - 2);
        token[len - 2] = '\0';
    }

    return token;
}

void free_token_list(TokenList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->tokens[i]);
    }
    free(list->tokens);
    free(list);
}

char *expand_variables(const char *input) {
    char *output = malloc(4096);
    char *out_ptr = output;
    const char *in_ptr = input;
	bool is_single_quote = false;

	if (in_ptr[0] == '\'')
		is_single_quote = true;		
    while (*in_ptr) {
        if (*in_ptr == '$' && !is_single_quote && (ft_isalnum(*(in_ptr + 1)) || *(in_ptr + 1) == '{')) {
            if (*(in_ptr + 1) == '{')
				in_ptr += 2;
			else
				in_ptr += 1;
            char var_name[256];
            char *var_name_ptr = var_name;

            while (*in_ptr && ( *in_ptr != '}' && !is_quote(*in_ptr) && !is_delimiter(*in_ptr))) {
                *var_name_ptr++ = *in_ptr++;
            }
            if (*in_ptr && *in_ptr == '}') {
                in_ptr++;
            }
            *var_name_ptr = '\0';

            char *var_value = getenv(var_name);
            if (var_value) {
                strcpy(out_ptr, var_value);
                out_ptr += strlen(var_value);
            }
        } else {
            *out_ptr++ = *in_ptr++;
        }
    }
    *out_ptr = '\0';

    return output;
}

TokenList *ft_tokenize(char *input) {
    TokenList *list = malloc(sizeof(TokenList));
    list->tokens = malloc(sizeof(char *) * MAX_TOKENS);
    list->count = 0;

    bool in_single_quote = false;
    bool in_double_quote = false;
    char *token_start = NULL;

    for (char *p = input; *p; p++) {
        if (is_quote(*p)) {
            if (*p == '\'' && !in_double_quote) {
                in_single_quote = !in_single_quote;
            } else if (*p == '\"' && !in_single_quote) {
                in_double_quote = !in_double_quote;
            }
        }
        if (is_delimiter(*p) && !in_single_quote && !in_double_quote) {
            if (token_start) {
                *p = '\0';
                if (list->count < MAX_TOKENS) {
                    list->tokens[list->count++] = expand_variables(token_start);
                }
                token_start = NULL;
            }
        } else if (!token_start) {
            token_start = p;
        }
    }
    if (token_start && list->count < MAX_TOKENS) {
        	list->tokens[list->count++] = expand_variables(token_start);
	}

    return list;
}
