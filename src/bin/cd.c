/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:27:23 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/23 12:52:42 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(t_shell *shell)
{
	t_parser *parser;
	char	*home;
	
	parser = shell->parser;
	home = getenv("HOME");
	if ((char *)shell->parser->args == NULL || ft_strncmp((char *)shell->parser->args->content, "~", 1) == 0)
	{
		if (chdir(home)== 0)
			error(shell, NULL, NULL);
		else
			error(shell, "cd: %s: No such file or directory\n", home);
	}
	else if (chdir((char  *)shell->parser->args->content) == 0)
		error(shell, NULL, NULL);
	else
		error(shell, "cd: %s: No such file or directory\n", (char *)shell->parser->args->content);
}
