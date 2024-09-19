/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/19 13:49:46 by chbachir         ###   ########.fr       */
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
 		add_history(shell.cmdline);
		lexer(&shell);
		expander(&shell);
		print_lexer(shell);// optional only printing: delete after finish
		printf("------------------------------------------------\n");

		parser(&shell);
		//print_cmdtable(shell);
		printf("------------------------------------------------\n");

		t_parser *current_node = shell.parser;
		while (current_node)
		{
			t_parser *cmd = (t_parser *)current_node;
			while (cmd->full_cmd)
			{
				char *content = (char *)cmd->full_cmd->content;
				cmd->full_cmd = cmd->full_cmd->next;
				exec_bin(&shell, content, NULL);
				break ;
			}
			current_node = current_node->next;
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
