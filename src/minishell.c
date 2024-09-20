/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 18:37:32 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(char **env)
{
	struct s_shell	shell;

	shell.cmdline = NULL;
	shell.env = NULL;
	shell.lexer = NULL;
	shell.parser = NULL;
	init_env(&shell, env);
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
			while (cmd->args)
			{
				char *content = (char *)cmd->args->content;
				cmd->args = cmd->args->next;
				exec_bin(&shell, content);
				break ;
			}
			current_node = current_node->next;
		}
		//free(shell.cmdline);
		cleanup(&shell);
		printf("\n");
	}
	if (shell.env)
	{
		free_env(shell.env);
		shell.env = NULL;
	}
	if (shell.cmdline)
	{
		free(shell.cmdline);
		shell.cmdline = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	minishell(env);


	// char *cmd = "export";
	// char *args[] = {"unset", "A=Hello", "B=GoodBye", "C=Emre", NULL};
	// char *args2[] = {"unset", "MAIL", "C", NULL};

	// t_shell	shell;
	// shell.env = NULL;
	
	// exec_env(&shell);

	return (0);
}
