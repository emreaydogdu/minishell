/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/07/01 13:58:15 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char *line = NULL;
	size_t len = 0;

	while (1) {
		printf("\033[36;1m%s\033[0m", "➜ minishell$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		printf("%s", line);
		line[ft_strlen(line)-1] = '\0';
		// ... parse & execute with var line
		init_lexer(line);
	}
	free(line);
}

int main(int ac, char **av) 
{
	minishell();
	return (0);
}
