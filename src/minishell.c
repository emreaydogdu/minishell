/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/03 23:24:45 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	minishell(void)
{
	struct s_shell	shell;

	while (1)
	{
		shell.cmdline = readline("\033[36;1m ➜ minishell$ \033[0m");
		if (!shell.cmdline)
			return ;
		shell.cmdline[ft_strlen(shell.cmdline)] = '\0';
		add_history(shell.cmdline);
		lexer(&shell);
		expander(&shell);
		print_lexer(shell);// optional only printing: delete after finish

/*
	t_prompt prompt;
	prompt.cmds = NULL;
	prompt.envp = NULL;
	prompt.pid = getpid();
	parser(shell.lexer, &prompt);
	print_cmdtable(&prompt);
*/
	}
}

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	minishell();
	return (0);
}
