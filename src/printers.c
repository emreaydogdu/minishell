/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 23:19:16 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/17 14:25:08 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// todo: DELETE
void	print_lexer(t_shell shell)
{
	const char *enum_dict[] = { "ARG", "PIPE", "TOKEN_REDIR_APPEND", "TOKEN_REDIR_HEREDOC", "TOKEN_REDIR_OUT", "TOKEN_REDIR_IN"};
	if (shell.lexer == NULL)
		printf("Lexer is empty\n");

	while (shell.lexer != NULL)
	{
		printf("%20s - type: %6s  pos: %zu\n", shell.lexer->input, enum_dict[shell.lexer->type], shell.lexer->pos);
		shell.lexer = shell.lexer->next;
	}
}
