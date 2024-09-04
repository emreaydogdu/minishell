/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:34 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/04 12:29:34 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	t_lexer * lexer;

	lexer = shell->lexer;
	
	while (lexer)
	{
		if (lexer->input[0] == '$')
		{
			lexer->input++;
			// todo: check if arg is existing or not. reproduce bash behavior.
			lexer->input = getenv(lexer->input);
			printf("%s\n", lexer->input);
		}
		lexer = lexer->next;
	}
}
