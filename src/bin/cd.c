/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:27:23 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 18:41:03 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(t_shell *shell)
{
	t_parser *parser;
	
	parser = shell->parser;
	
	char	*home;

	home = getenv("HOME");
	if ((char *)shell->parser->args == NULL || ft_strncmp((char *)shell->parser->args, "~", 1) == 0)
	{
		if (chdir(home) == 0)
			printf("%s\n", ".");
	}
	else if (chdir(shell->parser->args) == 0)
		printf("%s\n", ".");
}
