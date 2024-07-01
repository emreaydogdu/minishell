/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/07/01 15:12:00 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void minishell()
{
	char *buf;

	while (1) {
		printf("\033[36;1m%s\033[0m", "➜ minishell$ ");
		buf = readline("");
		
		if (!buf)
			return ;
		buf[ft_strlen(buf)] = '\0';
		// ... parse & execute with var line
		init_lexer(buf);
	}
}

int main(int ac, char **av) 
{
	minishell();
	return (0);
}
