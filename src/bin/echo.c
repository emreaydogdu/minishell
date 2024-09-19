/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/19 15:05:38 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_echo(t_parser *parser) // t_shell *shell, int out
{
	while (parser->full_cmd != NULL)
	{
		if (parser->outfile != STDOUT_FILENO)
		{
			write(parser->outfile, (char *)parser->full_cmd->content, ft_strlen((char *)parser->full_cmd->content));
			if (parser->full_cmd->next)
				write(parser->outfile, " ", 1);
		}
		else
		{
			printf("%s", (char *)parser->full_cmd->content);
			if (parser->full_cmd->next)
				printf(" ");
		}
		parser->full_cmd = parser->full_cmd->next;
	}
	close(parser->outfile);
}
