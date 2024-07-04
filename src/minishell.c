/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/07/04 15:08:57 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void
int_handler(int status) {
	rl_on_new_line(); // Regenerate the prompt on a newline
	printf("%d\n", status); // Move to a new line
	rl_replace_line(""); // Clear the previous text
	rl_redisplay();
}


void minishell()
{
	t_shell	shell;

    shell.lexer = NULL;

	while (1) {
		signal(SIGINT, int_handler);
		shell.cmdline = readline("\033[36;1m➜ minishell$ \033[0m");
		
		if (!shell.cmdline)
			return ;
		shell.cmdline[ft_strlen(shell.cmdline)] = '\0';
        add_history(shell.cmdline);
		// ... parse & execute with var line
		init_lexer(shell);
	}
}

int main(int ac, char **av) 
{
	minishell();
	return (0);
}
