/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:54:47 by chbachir          #+#    #+#             */
/*   Updated: 2024/08/30 22:12:19 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lexer(t_shell shell)
{
	const char *enum_dict[] = { "NOF", "PIPE", "TOKEN_REDIR_APPEND", "TOKEN_REDIR_HEREDOC", "TOKEN_REDIR_OUT", "TOKEN_REDIR_IN"};
	if (shell.lexer == NULL)
		printf("Lexer is empty\n");
	while (shell.lexer != NULL)
	{
		printf("%20s - type: %6s  pos: %zu\n", shell.lexer->input, enum_dict[shell.lexer->type], shell.lexer->pos);
		shell.lexer = shell.lexer->next;
	}
}

int	push(t_lexer **lexer, char *input, t_token_type type, size_t pos)
{
	t_lexer* token = malloc(sizeof(t_lexer));

	// Assign data to the new TOKEN
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
	t_lexer* last = *lexer;
	while (last->next != NULL)
		last = last->next;

	// Change the next of last node
	last->next = token;
	return (1);
}

void decode_lexer(char **str, t_shell *shell)
{
	size_t i = 0;
	size_t pos = 0;

	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], "|", 1) == 0)
			push(&shell->lexer, "|", TOKEN_PIPE, pos);
		else if (ft_strncmp(str[i], "<<", 2) == 0)
			push(&shell->lexer, "<<", TOKEN_REDIR_APPEND, pos);
		else if (ft_strncmp(str[i], ">>", 2) == 0)
			push(&shell->lexer, ">>", TOKEN_REDIR_HEREDOC, pos);
		else if (ft_strncmp(str[i], "<", 1) == 0)
			push(&shell->lexer, "<", TOKEN_REDIR_OUT, pos);
		else if (ft_strncmp(str[i], ">", 1) == 0)
			push(&shell->lexer, ">", TOKEN_REDIR_IN, pos);
		else
			push(&shell->lexer, str[i], TOKEN_NOF, pos);
		pos++;
		i++;
	}
}

t_lexer		*init_lexer(t_shell shell)
{
	char **str = ft_split(shell.cmdline, ' ');
	decode_lexer(str, &shell);
	expander(&shell);
	print_lexer(shell);
	return (NULL);
}
