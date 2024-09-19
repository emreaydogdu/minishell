/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/19 12:28:59 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(void)
{
	struct s_shell	shell;

	shell.cmdline = NULL;
	shell.env = NULL;
	shell.lexer = NULL;
	shell.parser = NULL;
	while (1)
	{
 		shell.cmdline = readline("\033[36;1m ➜ minishell$ \033[0m");
		if (!shell.cmdline)
			return ; 
		shell.cmdline[ft_strlen(shell.cmdline)] = '\0';

		//shell.cmdline = "echo 'hello' 'Emre'";
 		//add_history(shell.cmdline);
		lexer(&shell);
		expander(&shell);
		print_lexer(shell);// optional only printing: delete after finish
		printf("------------------------------------------------\n");

		parser(&shell);
		print_cmdtable(shell);
		printf("------------------------------------------------\n");
		while (shell.parser)
		{
			while (shell.parser->full_cmd)
			{
				char *content = (char *)shell.parser->full_cmd->content;
				shell.parser->full_cmd = shell.parser->full_cmd->next;
				exec_bin(&shell, content, NULL);
				break ;
			}
			shell.parser = shell.parser->next;
		}
		cleanup(&shell);
		printf("\n");
		//free(shell.cmdline);
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
