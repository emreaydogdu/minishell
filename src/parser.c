/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:05 by emaydogd          #+#    #+#             */
/*   Updated: 2024/07/02 11:49:05 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parser(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		if (lexer->type == TOKEN_PIPE)
		{
			printf("PIPE\n");
		}
		lexer = lexer->next;
	}
	return (0);
}