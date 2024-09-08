/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/08 22:11:46 by emaydogd         ###   ########.fr       */
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
		//print_lexer(shell);// optional only printing: delete after finish


		t_prompt	prompt;
		prompt.cmds = NULL;
		prompt.pid = getpid();
		parser(&shell, &prompt);
		print_cmdtable(&prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	//minishell();


	char *cmd = "export";
	char *args[] = {"export", "~", NULL};
	t_shell	shell;
	shell.env = NULL;
	init_env(&shell, env);
	exec_env(&shell);

	return (0);
}
