/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/12 11:59:16 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_shell *shell)
{
	free_lexer(&shell);
	free_parser(&shell);
	free_env(&shell);
	free(shell->cmdline);
}

void	free_lexer(t_shell *shell)
{
	t_lexer	*current_lexer;
	t_lexer *next;
	
	current_lexer = shell->lexer;
	while(current_lexer)
	{
		next = current_lexer->next;
		free(current_lexer->input);
		free(current_lexer);
		current_lexer = next;
	}
}

void	free_parser(t_shell *shell)
{
	t_parser *current_parser;
	t_parser *next;
	current_parser = shell->parser;

	while (current_parser)
	{
		next = current_parser->next;
		ft_lstclear(&current_parser->full_cmd, free);
		free(current_parser->full_path);
		free(current_parser);
		current_parser = next;
	}
}
void	free_env(t_shell *shell)
{
	t_env *current_env;
	t_env *next;
	current_env = shell->env;

	while (current_env)
	{
		next = current_env->next;
		free(current_env->key);
		free(current_env->value);
		free(current_env);
		current_env = next;
	}
}

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
			exec_exit(&shell);
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
