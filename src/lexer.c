/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:54:47 by chbachir          #+#    #+#             */
/*   Updated: 2024/07/01 15:09:25 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_lexer(t_lexer *lexer)
{
	const char *enum_dick[] = { "|" };
	while (lexer != NULL)
	{
		printf("%s - type: %s  \n", lexer->input, enum_dick[lexer->type]);
		lexer = lexer->next;
	}
}

t_lexer		*init_lexer(char *input)
{
	t_lexer			*list;

	list = malloc(sizeof(t_lexer));
	if (!list)
		return (NULL);
	while (*input)
	{
		if (*input == '|')
		{
			list->type = TOKEN_PIPE;
			list->input = "|";
			//list->pos = 
			list->next = NULL;
		}
		input++;
	}
	print_lexer(list);
	return (NULL);
}
