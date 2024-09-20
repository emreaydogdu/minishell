/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 18:35:21 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_echo(t_shell *shell) // t_shell *shell, int out
{
	t_parser *parser;
	
	parser = shell->parser;
	while (parser->args != NULL)
	{
		if (parser->outfile != STDOUT_FILENO)
		{
			write(parser->outfile, (char *)parser->args->content, ft_strlen((char *)parser->args->content));
			if (parser->args->next)
				write(parser->outfile, " ", 1);
		}
		else
		{
			printf("%s", (char *)parser->args->content);
			if (parser->args->next)
				printf(" ");
		}
		parser->args = parser->args->next;
	}
	if (parser->outfile != STDOUT_FILENO)
		close(parser->outfile);
}
