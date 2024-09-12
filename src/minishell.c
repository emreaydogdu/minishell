/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/12 11:15:10 by chbachir         ###   ########.fr       */
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
		printf("------------------------------------------------\n");

		if (ft_strncmp(shell.cmdline, "exit", 4) == 0 && (shell.cmdline[4] == '\0' || shell.cmdline[4] == ' '))
			exec_exit();
		parser(&shell);
		print_cmdtable(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	minishell();

/*
	char *cmd = "export";
	char *args[] = {"unset", "A=Hello", "B=GoodBye", "C=Emre", NULL};
	char *args2[] = {"unset", "MAIL", "C", NULL};

	t_shell	shell;
	shell.env = NULL;
	init_env(&shell, env);
	exec_env(&shell);
*/
	return (0);
}
