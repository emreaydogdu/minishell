/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:54:47 by chbachir          #+#    #+#             */
/*   Updated: 2024/07/02 14:32:27 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lexer(t_shell shell)
{
	const char *enum_dict[] = { "WORD", "PIPE" };
	while (shell.lexer != NULL)
	{
		printf("%10s - type: %6s  pos: %zu\n", shell.lexer->input, enum_dict[shell.lexer->type], shell.lexer->pos);
		shell.lexer = shell.lexer->next;
	}
}

int	push(t_lexer **lexer, char *input, t_token_type type, size_t pos) {
	struct s_lexer* token = malloc(sizeof(t_lexer));

	// Assign data to the new node
	token->input = input;
	token->type = type;
	token->pos = pos;
	token->next = NULL;

	// If the linked list is empty, then make the new node as head
	if (*lexer == NULL) {
		*lexer = token;
		return (1);
	}

	// Else traverse till the last node
	struct s_lexer* last = *lexer;
	while (last->next != NULL) {
		last = last->next;
	}

	// Change the next of last node
	last->next = token;
	return (1);
}

char *search_cmd(const char *str, size_t start, size_t end)
{
	char *ret = malloc(end - start + 1);
	size_t i = 0;

	while (start < end)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

t_lexer		*init_lexer(t_shell shell)
{
	size_t	pos = 0;
	size_t	start = 0;
	size_t	count = 0;

	while (shell.cmdline[count] != '\0')
	{
		if (shell.cmdline[count] == ' ')
		{
			if (start != 0)
			{
				pos += push(&shell.lexer, search_cmd(shell.cmdline, start-1, count), TOKEN_NOF, pos);
				start = 0;
			}
		}
		else if (shell.cmdline[count] == '|')
		{
			if (start != 0)
			{
				pos += push(&shell.lexer, search_cmd(shell.cmdline, start-1, count-1), TOKEN_NOF, pos);
				start = 0;
			}
			pos += push(&shell.lexer, "|", TOKEN_PIPE, pos);
		}
		else
		{
			if (start == 0)
				start = count;
		}
		count++;
	}
	if (start != 0)
		push(&shell.lexer, search_cmd(shell.cmdline, start-1, count), TOKEN_NOF, pos);
	print_lexer(shell);
	return (NULL);
}
